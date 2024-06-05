#include "Matrix.hpp"

//TODO update style to match CONTRIBUTING.md

namespace OpenArabTools {
	Matrix::Matrix() noexcept 
	: mSizeX(0), mSizeY(0), mrColor(nullptr), mrIsOn(nullptr), mInit(false) {}

	Matrix::Matrix(const U64 aSizeX, const U64 aSizeY) noexcept {
		this->mInit = false;
		this->set(aSizeX, aSizeY);
	}
	Matrix::Matrix(const Matrix& aOther) noexcept
		: mSizeX(0), mSizeY(0), mrColor(nullptr), mrIsOn(nullptr), mInit(false) {
		if (!aOther.mInit) {
			return; //aOther not initialized
		}
		if (&aOther == this) {
			Error::error("Matrix copy self assigment detected."); return;
		}

		this->mInit = false;
		this->mWindow = Internal::GLWindow(aOther.mSizeX, aOther.mSizeY);
		this->set(aOther.mSizeX, aOther.mSizeY);

		for (U64 i = 0; i < aOther.mSizeX * aOther.mSizeY; i++) {
			this->mrColor[i] = aOther.mrColor[i];
			this->mrIsOn[i] = aOther.mrIsOn[i];
		}
		this->UploadColorToShader();
		this->UploadStateToShader();
	}
	Matrix::Matrix(Matrix&& aOther) noexcept {
		this->mSizeX = aOther.mSizeX;
		this->mSizeY = aOther.mSizeY;
		this->mWindow = aOther.mWindow;
		this->mrColor = aOther.mrColor;
		this->mColorBuf = aOther.mColorBuf;
		this->mrIsOn = aOther.mrIsOn;
		this->mIsOnBuf = aOther.mIsOnBuf;
		this->mInit = aOther.mInit;

		//we take ownership, no free in aOther (we free), do so with all pointers
		aOther.mInit = false; //this covers mIsOn, mColor
	}
	Matrix& Matrix::operator=(const Matrix& aOther) noexcept {
		if (!aOther.mInit) {
			this->reset(); return *this; //aOther not initialized
		}
		if (&aOther == this) {
			Error::error("Matrix copy self assigment detected."); return *this;
		}

		this->reset();
		this->mWindow = Internal::GLWindow(aOther.mSizeX, aOther.mSizeY);
		this->set(aOther.mSizeX, aOther.mSizeY);

		for (U64 i = 0; i < aOther.mSizeX * aOther.mSizeY; i++) {
			this->mrColor[i] = aOther.mrColor[i];
			this->mrIsOn[i] = aOther.mrIsOn[i];
		}
		this->UploadColorToShader();
		this->UploadStateToShader();

		return *this;
	}
	Matrix& Matrix::operator=(Matrix&& aOther) noexcept {
		if (!aOther.mInit) {
			this->reset();
			return *this; //aOther not initialized
		}
		if (&aOther == this) {
			Error::error("Matrix copy self assigment detected."); return *this;
		}

		this->mSizeX = aOther.mSizeX;
		this->mSizeY = aOther.mSizeY;
		this->mWindow = aOther.mWindow;
		this->mrColor = aOther.mrColor;
		this->mColorBuf = aOther.mColorBuf;
		this->mrIsOn = aOther.mrIsOn;
		this->mIsOnBuf = aOther.mIsOnBuf;
		this->mInit = aOther.mInit;

		aOther.mInit = false; //same as in move constructor

		return *this;
	}

	void Matrix::showWindow() noexcept {
		this->mWindow.ShowWindow();
		this->mWindow.BindContext();
		this->mWindow.PrepareUniforms(this->mSizeX, this->mSizeY);
	}
	void Matrix::hideWindow() noexcept {
		this->mWindow.HideWindow();
	}

	//setters

	void Matrix::setTitle(const std::string& aTitle) noexcept {
		this->mWindow.SetTitle(aTitle.c_str());
	}

	void Matrix::setBackground(const LightColor aColor) noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrColor[i].SetB(aColor);
		}
		this->UploadColorToShader();
	}
	void Matrix::setBackground(const U64 aId, const LightColor& aColor) noexcept {
		this->mrColor[aId].SetB(aColor);
		this->UploadColorToShader();
	}
	void Matrix::setBackground(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept {
		this->mrColor[aColumn + (aRow * this->mSizeX)].SetB(aColor);
		this->UploadColorToShader();
	}
	void Matrix::setColor(const LightColor& aColor) noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrColor[i].SetF(aColor);
		}
		this->UploadColorToShader();
	}
	void Matrix::setColor(const U64 aId, const LightColor& aColor) noexcept {
		this->mrColor[aId].SetF(aColor);
		this->UploadColorToShader();
	}
	void Matrix::setColor(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept {
		this->mrColor[aColumn + (aRow * this->mSizeX)].SetF(aColor);
		this->UploadColorToShader();
	}

	void Matrix::setOff() noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrIsOn[i] = false;
		}
		this->UploadStateToShader();
	}
	void Matrix::setOff(const U64 aId) noexcept {
		this->mrIsOn[aId] = false;
		this->UploadStateToShader();
	}
	void Matrix::setOff(const U64 aColumn, const U64 aRow) noexcept {
		this->mrIsOn[aColumn + (aRow * this->mSizeX)] = false;
		this->UploadStateToShader();
	}
	void Matrix::setOn() noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrIsOn[i] = true;
		}
		this->UploadStateToShader();
	}
	void Matrix::setOn(const U64 aId) noexcept {
		this->mrIsOn[aId] = true;
		this->UploadStateToShader();
	}
	void Matrix::setOn(const U64 aColumn, const U64 aRow) noexcept {
		this->mrIsOn[aColumn + (aRow * this->mSizeX)] = true;
		this->UploadStateToShader();
	}
	void Matrix::setOnOff(const bool aOnOff) noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrIsOn[i] = aOnOff;
		}
		this->UploadStateToShader();
	}
	void Matrix::setOnOff(const U64 aId, const bool aOnOff) noexcept {
		this->mrIsOn[aId] = aOnOff;
		this->UploadStateToShader();
	}
	void Matrix::setOnOff(const U64 aColumn, const U64 aRow, const bool aOnOff) noexcept {
		this->mrIsOn[aColumn + (aRow * this->mSizeX)] = aOnOff;
		this->UploadStateToShader();
	}

	//getters

	LightColor Matrix::getBackground() const noexcept {
		return { this->mrColor[0].BR, this->mrColor[0].BG, this->mrColor[0].BB };
	}
	LightColor Matrix::getBackground(const U64 aId) const noexcept {
		return { this->mrColor[aId].BR, this->mrColor[aId].BG, this->mrColor[aId].BB };
	}
	LightColor Matrix::getBackground(const U64 aColumn, const U64 aRow) const noexcept {
		return { this->mrColor[aColumn + (aRow * this->mSizeX)].BR, this->mrColor[aColumn + (aRow * this->mSizeX)].BG, this->mrColor[aColumn + (aRow * this->mSizeX)].BB };
	}
	LightColor Matrix::getColor(const U64 aId) const noexcept {
		return { this->mrColor[aId].FR, this->mrColor[aId].FG, this->mrColor[aId].FB };
	}
	LightColor Matrix::getColor() const noexcept {
		return { this->mrColor[0].FR, this->mrColor[0].FG, this->mrColor[0].FB };
	}
	LightColor Matrix::getColor(const U64 aColumn, const U64 aRow) const noexcept {
		return { this->mrColor[aColumn + (aRow * this->mSizeX)].FR, this->mrColor[aColumn + (aRow * this->mSizeX)].FG, this->mrColor[aColumn + (aRow * this->mSizeX)].FB };
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
		return !bool(this->mrIsOn[0]);
	}
	bool Matrix::isOff(const U64 aId) const noexcept {
		return !bool(this->mrIsOn[aId]);
	}
	bool Matrix::isOff(const U64 aColumn, const U64 aRow) const noexcept {
		return !bool(this->mrIsOn[aColumn + (aRow * this->mSizeX)]);
	}
	bool Matrix::isOn() const noexcept {
		return bool(this->mrIsOn[0]);
	}
	bool Matrix::isOn(const U64 aId) const noexcept {
		return bool(this->mrIsOn[aId]);
	}
	bool Matrix::isOn(const U64 aColumn, const U64 aRow) const noexcept {
		return bool(this->mrIsOn[aColumn + (aRow * this->mSizeX)]);
	}

	//other stuff

	bool Matrix::open() const noexcept {
		return this->mWindow.IsWindowOpen();
	}

	bool Matrix::update() noexcept {
		if (!this->mInit) { 
			Error::warning("Updating dead Matrix object, consider checking return value.");
			return false;
		}
		if (!this->mWindow.IsWindowOpen()) {
			this->reset();
		}
		this->mColorBuf.Bind();
		this->mIsOnBuf.Bind();
		this->mWindow.glIBO.Draw();
		this->mWindow.Process();
		return this->mWindow.IsWindowOpen();
	}

	void Matrix::run() noexcept {
		while (this->open()) this->update();
	}

	//
	//openarabtools extensions
	//

	void Matrix::setOffColor(const LightColor& aColor) noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrColor[i].SetO(aColor);
		}
		this->UploadColorToShader();
	}
	void Matrix::setOffColor(const U64 aId, const LightColor& aColor) noexcept {
		this->mrColor[aId].SetO(aColor);
		this->UploadColorToShader();
	}
	void Matrix::setOffColor(const U64 aColumn, const U64 aRow, const LightColor& aColor) noexcept {
		this->mrColor[aColumn + (aRow * this->mSizeX)].SetO(aColor);
		this->UploadColorToShader();
	}
	
	void Matrix::setColorAlpha(const float aAlpha) noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrColor[i].FA = aAlpha;
		}
		this->UploadColorToShader();
	}
	void Matrix::setColorAlpha(const U64 aId, const float aAlpha) noexcept {
		this->mrColor[aId].FA = aAlpha;
	}
	void Matrix::setColorAlpha(const U64 aColumn, const U64 aRow, const float aAlpha) noexcept {
		this->mrColor[aColumn + (aRow * this->mSizeX)].FA = aAlpha;
	}
	void Matrix::setOffColorAlpha(const float aAlpha) noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrColor[i].OA = aAlpha;
		}
	}
	void Matrix::setOffColorAlpha(const U64 aId, const float aAlpha) noexcept {
		this->mrColor[aId].OA = aAlpha;
	}
	void Matrix::setOffColorAlpha(const U64 aColumn, const U64 aRow, const float aAlpha) noexcept {
		this->mrColor[aColumn + (aRow * this->mSizeX)].OA = aAlpha;
	}
	void Matrix::setBackgroundAlpha(const float aAlpha) noexcept {
		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrColor[i].BA = aAlpha;
		}
	}
	void Matrix::setBackgroundAlpha(const U64 aId, const float aAlpha) noexcept {
		this->mrColor[aId].BA = aAlpha;
	}
	void Matrix::setBackgroundAlpha(const U64 aColumn, const U64 aRow, const float aAlpha) noexcept {
		this->mrColor[aColumn + (aRow * this->mSizeX)].BA = aAlpha;
	}

	void Matrix::showWindowAndRun() noexcept {
		this->showWindow();
		this->run();
	}

	void Matrix::set(const U64 aSizeX, const U64 aSizeY) noexcept {
		if (this->mInit) {
			Error::error("Matrix already initialized.");
			this->reset(); return;
		}

		//variable setup
		this->mSizeX = aSizeX;
		this->mSizeY = aSizeY;

		//select larger (size X or size Y), size should never be larger than 800px
		U64 CircleSize = 800 / ((this->mSizeX > this->mSizeY) ? this->mSizeX : this->mSizeY);

		if (CircleSize > 130) {
			CircleSize = 130;
		}

		this->mWindow.Resize(this->mSizeX * CircleSize, this->mSizeY * CircleSize);

		this->mrColor = (Internal::CircleColor*)malloc(this->mSizeX * this->mSizeY * sizeof(Internal::CircleColor));
		if (this->mrColor == nullptr) {
			Error::error("Matrix setup error: allocation of Color array failed"); return;
		}

		this->mrIsOn = (int*)malloc(this->mSizeX * this->mSizeY * sizeof(int));
		if (this->mrIsOn == nullptr) {
			Error::error("Matrix setup error: allocation of IsOn array failed"); return;
		}

		for (U64 i = 0; i < this->mSizeX * this->mSizeY; i++) {
			this->mrColor[i] = 
				//RGBA: Color, RGBA: Off, RGBA Background
				//default: black on black in original, here will be white FG on black BG
				{
				1.0, 1.0, 1.0, 1.0, //FG
				0.0, 0.0, 0.0, 0.0, //OG
				0.0, 0.0, 0.0, 1.0  //BG
				};
			this->mrIsOn[i] = false; //start off
		}

		//generation

		float* VerticesData;
		U64 VertexSize = Internal::GenerateTileVertices(&VerticesData, this->mSizeX, this->mSizeY);
		unsigned int* IndicesData;
		Internal::GenerateTileIndices(&IndicesData, VertexSize / 4);

#ifdef OPENARABTOOLS_PRINT_DEBUG_INFO
		Error::warning("Debug log:");
		Internal::Debug::PrintVertexArray(&VerticesData, VertexSize, 4);
		Internal::Debug::PrintIndexArray(&IndicesData, VertexSize / 4, 6);
		Error::warning("End of debug log.");
#endif

		this->mWindow.glVBO.Bind();
		Internal::ApplyChangesV(&VerticesData, VertexSize, &this->mWindow.glVBO);

		if (this->mWindow.glVBO.AreCountersSaved()) {
			this->mWindow.glVBO.RestoreAttributes(&this->mWindow.glVAO);
		}
		else {
			this->mWindow.glVBO.EnableAttribute(2, &this->mWindow.glVAO); //2d pos
			this->mWindow.glVBO.EnableAttribute(2, &this->mWindow.glVAO); //top left
		}

		Internal::ApplyChangesI(&IndicesData, VertexSize / 4, &this->mWindow.glIBO);

		this->mWindow.PrepareUniforms(this->mSizeX, this->mSizeY);

		this->mColorBuf.Set(this->mrColor, this->mSizeX * this->mSizeY, &this->mWindow.glVAO);
		this->mIsOnBuf.Set(this->mrIsOn, this->mSizeX * this->mSizeY, &this->mWindow.glVAO);

		this->mWindow.ShowWindow();

		this->mInit = true;
	}

	void Matrix::reset() noexcept {
		if (!this->mInit) {
			Error::warning("Matrix reset called twice.");
			return;
		}

		//no window reset!
		this->mWindow.HideWindow();
		this->mSizeX = 0;
		this->mSizeY = 0;
		free(this->mrColor);
		free(this->mrIsOn);
		this->mInit = false;
	}

	void Matrix::resizeMatrix(const U64 aNewX, const U64 aNewY) noexcept {
		this->reset();
		this->set(aNewX, aNewY);
	}

	bool Matrix::sleep(const U64 aMs) noexcept {
		std::chrono::system_clock::time_point Start = std::chrono::system_clock::now();
		std::chrono::system_clock::time_point End = Start + std::chrono::milliseconds(aMs);

		while (std::chrono::system_clock::now() < End) {
			if (!this->mWindow.IsWindowOpen()) {
				this->reset();
				return false;
			}
			std::this_thread::sleep_for(1ms);
			this->mWindow.glIBO.Draw();
			this->mWindow.Process();
		}
		return true;
	}

	//
	//end of openarabtools extensions
	//

	Matrix::~Matrix() noexcept {
		//different from reset() function, no error handling
		if (!this->mInit) return;
		free(this->mrColor);
		free(this->mrIsOn);
	}

	//private

	void Matrix::UploadColorToShader() noexcept {
		glUseProgram(this->mWindow.glCircleShader);
		this->mColorBuf.Update(this->mrColor);
	}

	void Matrix::UploadStateToShader() noexcept {
		glUseProgram(this->mWindow.glCircleShader);
		this->mIsOnBuf.Update(this->mrIsOn);
	}

	void Matrix::CheckRangeID(const U64 aId) noexcept {

	}
	void Matrix::CheckRangeCR(const U64 aCol, const U64 aRow) noexcept {

	}
}