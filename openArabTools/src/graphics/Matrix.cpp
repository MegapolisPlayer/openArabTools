#include "Matrix.hpp"

namespace OpenArabTools {
	Matrix::Matrix() noexcept 
	: mSizeX(0), mSizeY(0), mColor(nullptr), mIsOn(nullptr), mResourcesTransferred(false) {}

	Matrix::Matrix(const U64 aSizeX, const U64 aSizeY) noexcept {
		this->set(aSizeX, aSizeY);
	}

	void Matrix::showWindow() noexcept {
		this->mWindow.ShowWindow();
	}
	void Matrix::hideWindow() noexcept {
		this->mWindow.HideWindow();
	}

	void Matrix::setTitle(const std::string& aTitle) noexcept {
		this->mWindow.SetTitle(aTitle.c_str());
	}

	void Matrix::setBackground(const LightColor aColor) noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mColor[i].SetB(aColor);
		}
		this->UploadColorToShader();
	}
	void Matrix::setBackground(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept {
		this->mColor[aColumn + (aRow * this->mSizeX)].SetB(aColor);
		this->UploadColorToShader();
	}
	void Matrix::setColor(const LightColor& aColor) noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mColor[i].SetF(aColor);
		}
		this->UploadColorToShader();
	}
	void Matrix::setColor(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept {
		this->mColor[aColumn + (aRow * this->mSizeX)].SetF(aColor);
		this->UploadColorToShader();
	}

	void Matrix::setOff() noexcept {
		this->mIsOn[0] = false;
		this->UploadStateToShader();
	}
	void Matrix::setOff(const U64 aId) noexcept {
		this->mIsOn[aId] = false;
		this->UploadStateToShader();
	}
	void Matrix::setOff(const U64 aColumn, const U64 aRow) noexcept {
		this->mIsOn[aColumn + (aRow * this->mSizeX)] = false;
		this->UploadStateToShader();
	}
	void Matrix::setOn() noexcept {
		this->mIsOn[0] = true;
		this->UploadStateToShader();
	}
	void Matrix::setOn(const U64 aId) noexcept {
		this->mIsOn[aId] = true;
		this->UploadStateToShader();
	}
	void Matrix::setOn(const U64 aColumn, const U64 aRow) noexcept {
		this->mIsOn[aColumn + (aRow * this->mSizeX)] = true;
		this->UploadStateToShader();
	}
	void Matrix::setOnOff(const bool aOnOff) noexcept {
		this->mIsOn[0] = aOnOff;
		this->UploadStateToShader();
	}
	void Matrix::setOnOff(const U64 aId, const bool aOnOff) noexcept {
		this->mIsOn[aId] = aOnOff;
		this->UploadStateToShader();
	}
	void Matrix::setOnOff(const U64 aColumn, const U64 aRow, const bool aOnOff) noexcept {
		this->mIsOn[aColumn + (aRow * this->mSizeX)] = aOnOff;
		this->UploadStateToShader();
	}

	LightColor Matrix::getBackground() const noexcept {
		return this->mPanelBG;
	}
	LightColor Matrix::getBackground(const U64 aColumn, const U64 aRow) const noexcept {
		return { this->mColor[aColumn + (aRow * this->mSizeX)].BR, this->mColor[aColumn + (aRow * this->mSizeX)].BG, this->mColor[aColumn + (aRow * this->mSizeX)].BB };
	}
	LightColor Matrix::getColor() const noexcept {
		return this->mDefaultFG;
	}
	LightColor Matrix::getColor(const U64 aColumn, const U64 aRow) const noexcept {
		return { this->mColor[aColumn + (aRow * this->mSizeX)].FR, this->mColor[aColumn + (aRow * this->mSizeX)].FG, this->mColor[aColumn + (aRow * this->mSizeX)].FB };
	}
	std::string Matrix::getTitle() const noexcept {
		return this->mWindow.GetTitle();
	}
	U64 Matrix::getWidth() const noexcept {
		return this->mSizeX;
	}
	U64 Matrix::getHeight() const noexcept {
		return this->mSizeY;
	}
	U64 Matrix::getSize() const noexcept {
		return this->mSizeX * this->mSizeY;
	}

	bool Matrix::isOff() const noexcept {
		return !bool(this->mIsOn[0]);
	}
	bool Matrix::isOff(const U64 aId) const noexcept {
		return !bool(this->mIsOn[aId]);
	}
	bool Matrix::isOff(const U64 aColumn, const U64 aRow) const noexcept {
		return !bool(this->mIsOn[aColumn + (aRow * this->mSizeX)]);
	}
	bool Matrix::isOn() const noexcept {
		return bool(this->mIsOn[0]);
	}
	bool Matrix::isOn(const U64 aId) const noexcept {
		return bool(this->mIsOn[aId]);
	}
	bool Matrix::isOn(const U64 aColumn, const U64 aRow) const noexcept {
		return bool(this->mIsOn[aColumn + (aRow * this->mSizeX)]);
	}

	bool Matrix::open() const noexcept {
		return this->mWindow.IsWindowOpen();
	}

	void Matrix::update() noexcept {
		this->mWindow.PrepareUniforms(this->mSizeX, this->mSizeY);
		this->mColorBuf.Bind();
		this->mIsOnBuf.Bind();
		this->mWindow.glIBO.Draw();
		this->mWindow.Process();
	}

	void Matrix::run() noexcept {
		while (this->open()) this->update();
	}

	//
	//openarabtools extensions
	//

	void Matrix::set(const U64 aSizeX, const U64 aSizeY) noexcept {
		//variable setup
		this->mSizeX = aSizeX;
		this->mSizeY = aSizeY;

		this->mColor = (Internal::CircleColor*)malloc(this->mSizeX * this->mSizeY * sizeof(Internal::CircleColor));

		this->mIsOn = (int*)malloc(this->mSizeX * this->mSizeY * sizeof(int));

		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mColor[i] = 
				//RGBA: Color, RGBA: Off (alpha 0), RGBA Background
				//default: black on black in original, here will be white FG on black BG
				{
				1.0, 1.0, 1.0, 1.0, //FG
				0.0, 0.0, 0.0, 0.0, //OG
				0.0, 0.0, 0.0, 1.0  //BG
				};
			this->mIsOn[i] = true;
		}

		//generation

		float* VerticesData;
		U64 VertexSize = Internal::GenerateTileVertices(&VerticesData, this->mSizeX, this->mSizeY);
		unsigned int* IndicesData;
		Internal::GenerateTileIndices(&IndicesData, VertexSize / 4);

#ifdef _DEBUG
		std::cout << "openArabTools: DEBUG log:\n";
		Internal::Debug::PrintVertexArray(&VerticesData, VertexSize, 4);
		Internal::Debug::PrintIndexArray(&IndicesData, VertexSize / 4, 6);
		std::cout << "openArabTools: DEBUG log completed.\n";
#endif

		Internal::ApplyChangesV(&VerticesData, VertexSize, &this->mWindow.glVBO);
		this->mWindow.glVBO.EnableAttribute(2, &this->mWindow.glVAO); //2d pos
		this->mWindow.glVBO.EnableAttribute(2, &this->mWindow.glVAO); //top left
		Internal::ApplyChangesI(&IndicesData, VertexSize / 4, &this->mWindow.glIBO);

		this->mWindow.PrepareUniforms(this->mSizeX, this->mSizeY);
		this->UploadColorToShader();
		this->UploadStateToShader();
	}

	void Matrix::resizeMatrix(const U64 aNewX, const U64 aNewY) noexcept {
		return;

		this->mSizeX = aNewX;
		this->mSizeY = aNewY;

		//TODO: realloc buffers
		//TODO: finish matrix class
	}

	//TODO: maybe add controls for offColor (O)

	//
	//end of openarabtools extensions
	//

	Matrix::~Matrix() noexcept {
		free(this->mColor);
		free(this->mIsOn);
	}

	//private

	void Matrix::UploadColorToShader() noexcept {
		this->mColorBuf.Set(this->mColor, this->mSizeX * this->mSizeY, &this->mWindow.glVAO);
	}

	void Matrix::UploadStateToShader() noexcept {
		this->mIsOnBuf.Set(this->mIsOn, this->mSizeX * this->mSizeY, &this->mWindow.glVAO);
	}
}