#include "Canvas.hpp"

namespace OpenArabTools {
	Shape::Shape() noexcept
		: mX(0), mY(0), mSizeX(0), mSizeY(0), mColor(LIGHTCOLOR_BLACK), mUsesRoundedShader(false) {}

#ifndef OPENARABTOOLS_NO_DAISYCHAIN
	Shape& Shape::setX(const uint64_t aX) noexcept {
		this->mX = aX;
		return *this;
	}
	Shape& Shape::setY(const uint64_t aY) noexcept {
		this->mY = aY;
		return *this;
	}
	Shape& Shape::setPosition(const uint64_t aX, const uint64_t aY) noexcept {
		this->mX = aX;
		this->mY = aY;
		return *this;
	}

	Shape& Shape::setColor(const LightColor& aColor) noexcept {
		this->mColor = aColor;
		return *this;
	}
	Shape& Shape::resetColor() noexcept {
		this->mColor = LIGHTCOLOR_BLACK;
		return *this;
	}
#else
	void Shape::setX(const uint64_t aX) noexcept {
		this->mX = aX;
	}
	void Shape::setY(const uint64_t aY) noexcept {
		this->mY = aY;
	}
	void Shape::setPosition(const uint64_t aX, const uint64_t aY) noexcept {
		this->mX = aX;
		this->mY = aY;
	}

	void Shape::setColor(const LightColor& aColor) noexcept {
		this->mColor = aColor;
	}
	void Shape::resetColor() noexcept {
		this->mColor = LIGHTCOLOR_BLACK;
	}
#endif

	uint64_t Shape::getX() const noexcept {
		return this->mX;
	}
	uint64_t Shape::getY() const noexcept {
		return this->mY;
	}
	LightColor Shape::getColor() const noexcept {
		return this->mColor;
	}

	Shape::~Shape() noexcept {}

	Square::Square() noexcept
		: Shape() {
		this->mSizeX = 10;
		this->mSizeY = 10;
	}

	//we duplicate methods in children to override their return type from Shape& to the type of the child

#ifndef OPENARABTOOLS_NO_DAISYCHAIN
	Square& Square::setX(const uint64_t aX) noexcept {
		return (Square&)Shape::setX(aX);
	}
	Square& Square::setY(const uint64_t aY) noexcept {
		return (Square&)Shape::setY(aY);
	}
	Square& Square::setPosition(const uint64_t aX, const uint64_t aY) noexcept {
		return (Square&)Shape::setPosition(aX, aY);
	}

	Square& Square::setColor(const LightColor& aColor) noexcept {
		return (Square&)Shape::setColor(aColor);
	}
	Square& Square::resetColor() noexcept {
		return (Square&)Shape::resetColor();
	}
#endif

	Square& Square::setWidth(const uint64_t aWidth) noexcept {
		this->mSizeX = aWidth; this->mSizeY = aWidth;
		return *this;
	}
	uint64_t Square::getWidth() const noexcept {
		return this->mSizeX;
	}

	Square::~Square() noexcept {}

	Circle::Circle() noexcept
		: Shape() {
		this->mSizeX = 10;
		this->mSizeY = 10;
		this->mUsesRoundedShader = true;
	}

#ifndef OPENARABTOOLS_NO_DAISYCHAIN
	Circle& Circle::setX(const uint64_t aX) noexcept {
		return (Circle&)Shape::setX(aX);
	}
	Circle& Circle::setY(const uint64_t aY) noexcept {
		return (Circle&)Shape::setY(aY);
	}
	Circle& Circle::setPosition(const uint64_t aX, const uint64_t aY) noexcept {
		return (Circle&)Shape::setPosition(aX, aY);
	}

	Circle& Circle::setColor(const LightColor& aColor) noexcept {
		return (Circle&)Shape::setColor(aColor);
	}
	Circle& Circle::resetColor() noexcept {
		return (Circle&)Shape::resetColor();
	}
#endif

	Circle& Circle::setRadius(const uint64_t aRadius) noexcept {
		this->mSizeX = aRadius*2; this->mSizeY = aRadius*2; //change radius to diameter
		return *this;
	}
	uint64_t Circle::getRadius() const noexcept {
		return this->mSizeX;
	}

	Circle::~Circle() noexcept {}

	Rectangle::Rectangle() noexcept 
		: Shape() {
		this->mSizeX = 20;
		this->mSizeY = 10;
	}

#ifndef OPENARABTOOLS_NO_DAISYCHAIN
	Rectangle& Rectangle::setX(const uint64_t aX) noexcept {
		return (Rectangle&)Shape::setX(aX);
	}
	Rectangle& Rectangle::setY(const uint64_t aY) noexcept {
		return (Rectangle&)Shape::setY(aY);
	}
	Rectangle& Rectangle::setPosition(const uint64_t aX, const uint64_t aY) noexcept {
		return (Rectangle&)Shape::setPosition(aX, aY);
	}

	Rectangle& Rectangle::setColor(const LightColor& aColor) noexcept {
		return (Rectangle&)Shape::setColor(aColor);
	}
	Rectangle& Rectangle::resetColor() noexcept {
		return (Rectangle&)Shape::resetColor();
	}
#endif

	Rectangle& Rectangle::setWidth(const uint64_t aWidth) noexcept {
		this->mSizeX = aWidth;
		return *this;
	}
	Rectangle& Rectangle::setHeight(const uint64_t aHeight) noexcept {
		this->mSizeY = aHeight;
		return *this;
	}

	uint64_t Rectangle::getWidth() const noexcept {
		return this->mSizeX;
	}
	uint64_t Rectangle::getHeight() const noexcept {
		return this->mSizeY;
	}

	Rectangle::~Rectangle() noexcept {}

	//Canvas
	static constexpr uint64_t csMaxDrawableObjects = 2048;
	static constexpr uint64_t csVertexSize = 11; //2 for pos, 2 for top left, 1 for outer opacity, 4 color

	Canvas::Canvas() noexcept
		: mVBOData(nullptr), mInit(false) {
		this->set(600, 300, "openArabTools Canvas");
	}
	Canvas::Canvas(const std::string& aTitle) noexcept
		: mVBOData(nullptr), mInit(false) {
		this->set(600, 300, aTitle);
	}
	Canvas::Canvas(const uint64_t aWidth, const uint64_t aHeight, const std::string& aTitle) noexcept
		: mVBOData(nullptr), mInit(false) {
		this->set(aWidth, aHeight, aTitle);
	}

	Canvas::Canvas(const Canvas& aOther) noexcept
		: mVBOData(nullptr), mInit(false) {
		if (!aOther.mInit) {
			return; //aOther not initialized
		}
		if (&aOther == this) {
			Error::error("Canvas copy self assigment detected."); return;
		}

		this->set(aOther.mWindow.SizeX(), aOther.mWindow.SizeY(), aOther.mWindow.GetTitle());
	}
	Canvas::Canvas(Canvas&& aOther) noexcept {
		this->mWindow = std::move(aOther.mWindow);
		this->mShapes = std::move(aOther.mShapes);
		this->mVBOData = aOther.mVBOData;
		aOther.mVBOData = nullptr;
		this->mInit = aOther.mInit;
		aOther.mInit = false;
	}
	Canvas& Canvas::operator=(const Canvas& aOther) noexcept {
		if (!aOther.mInit) {
			this->reset(); return *this; //aOther not initialized
		}
		if (&aOther == this) {
			Error::error("Canvas copy self assigment detected."); return *this;
		}

		if (this->mInit) {
			this->reset();
		}
		//inits VBOData, Init
		this->set(aOther.mWindow.SizeX(), aOther.mWindow.SizeY(), aOther.mWindow.GetTitle());

		return *this;
	}
	Canvas& Canvas::operator=(Canvas&& aOther) noexcept {
		this->mWindow = std::move(aOther.mWindow);
		this->mShapes = std::move(aOther.mShapes);
		this->mVBOData = aOther.mVBOData;
		aOther.mVBOData = nullptr;
		this->mInit = aOther.mInit;
		aOther.mInit = false;
		return *this;
	}

	uint64_t Canvas::add(const Shape& aShape) noexcept {
		this->mShapes.push_back(aShape);
		uint64_t ShapeId = this->mShapes.size() - 1;

		this->updateVBOData(ShapeId, aShape);

		return ShapeId; //id of shape
	}
	uint64_t Canvas::updateShape(const uint64_t aShapeId, const Shape& aNewData) noexcept {
		if (aShapeId >= this->mShapes.size()) {
			Error::error("Requested ID is out of range!"); return INT64_MAX;
		}
		this->mShapes[aShapeId] = aNewData;
		this->updateVBOData(aShapeId, aNewData);
		return aShapeId;
	}
	void Canvas::remove(const uint64_t aShapeId) noexcept {
		for (uint64_t i = 0; i < this->mShapes.size(); i++) {
			if (i == aShapeId) {
				this->mShapes.erase(this->mShapes.begin() + i);
				this->eraseVBOData(aShapeId);
				return;
			}
		}
		Error::warning("Requested shape not found!");
	}
	void Canvas::clear() noexcept {
		this->mShapes.clear();
		this->update();
	}

	void Canvas::setBackground(const LightColor& aLC) noexcept {
		this->mWindow.SetBackground(aLC.R, aLC.G, aLC.B, 1.0f);
	}

	void Canvas::paint() noexcept {
		this->update();
	}

	bool Canvas::open() const noexcept {
		return this->mWindow.IsWindowOpen();
	}
	bool Canvas::update() noexcept {
		if (!this->mInit) {
			Error::warning("Updating dead Canvas object, consider checking return value of update().");
			return false;
		}
		if (!this->mWindow.IsWindowOpen()) {
			this->reset();
		}
		if (this->mWindow.IsWindowHidden()) {
			this->mWindow.ShowWindow();
		}

		this->mWindow.BindContext();
		this->mWindow.glVAO.Bind();
		this->mWindow.BindShader();

		this->mWindow.glIBO.Draw();

		this->mWindow.Process();
		return this->mWindow.IsWindowOpen();
	}
	void Canvas::run() noexcept {
		while (this->open()) { this->update(); }
	}

	void Canvas::showWindow() noexcept {
		this->mWindow.ShowWindow();
	}
	void Canvas::hideWindow() noexcept {
		this->mWindow.HideWindow();
	}

	void Canvas::setTitle(const std::string& aTitle) noexcept {
		this->mWindow.SetTitle(aTitle.c_str());
	}

	void Canvas::set(const uint64_t aWidth, const uint64_t aHeight, const std::string& aTitle) noexcept {
		this->mWindow.SetTitle(aTitle.c_str());
		this->mWindow.Resize(aWidth, aHeight);
		this->mWindow.BindContext();
		this->mWindow.BindShader();
		glUniform2f(this->mWindow.glWindowResolutionUniform, aWidth, aHeight);

		this->mWindow.SetBackground(0.5, 1.0); //LIGHTCOLOR_GRAY

		this->mWindow.glVAO.Bind();

		//setup VBO

		this->mVBOData = (GLfloat*)malloc(csMaxDrawableObjects * 4 * csVertexSize * sizeof(GLfloat));
		if (this->mVBOData == NULL) { Error::error("Matrix setup error: allocation of VBO array failed"); return; }

		for (uint64_t i = 0; i < csMaxDrawableObjects * 4 * csVertexSize; i++) { this->mVBOData[i] = 0.0f; }
		this->mWindow.glVBO.Set(this->mVBOData, csMaxDrawableObjects * 4, csVertexSize);
		this->mWindow.glVBO.EnableAttribute(2, &this->mWindow.glVAO);
		this->mWindow.glVBO.EnableAttribute(2, &this->mWindow.glVAO);
		this->mWindow.glVBO.EnableAttribute(2, &this->mWindow.glVAO);
		this->mWindow.glVBO.EnableAttribute(1, &this->mWindow.glVAO);
		this->mWindow.glVBO.EnableAttribute(4, &this->mWindow.glVAO);

		free(this->mVBOData);

		//setup IBO

		GLuint* IBOData = (GLuint*)malloc(csMaxDrawableObjects * 6 * sizeof(GLuint));
		if (IBOData == NULL) { Error::error("Matrix setup error: allocation of IBO array failed"); return; }

		//0, 1, 2
		//2, 3, 0
		for (uint64_t i = 0; i < csMaxDrawableObjects * 6; i+=6) {
			IBOData[i + 0] = 0 + uint64_t(i / 6 * 4); IBOData[i + 1] = 1 + uint64_t(i / 6 * 4);	IBOData[i + 2] = 2 + uint64_t(i / 6 * 4);
			IBOData[i + 3] = 2 + uint64_t(i / 6 * 4); IBOData[i + 4] = 3 + uint64_t(i / 6 * 4);	IBOData[i + 5] = 0 + uint64_t(i / 6 * 4);
		}

		this->mWindow.glIBO.Set(IBOData, csMaxDrawableObjects * 6); //IBO is set in stone - we always have X amount of objects and they have 4 vertices (2x triangle)
		free(IBOData);

		this->mWindow.ShowWindow();

		this->mInit = true;
	}
	void Canvas::reset() noexcept {
		if (!this->mInit) {
			return;
		}

		this->mWindow.HideWindow();

		this->mShapes.clear();
		this->mInit = false;
	}

	void Canvas::showWindowAndRun() noexcept {
		this->showWindow();
		this->run();
	}
	bool Canvas::sleep(const uint64_t aMs) noexcept {
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

	Canvas::~Canvas() noexcept {
		this->reset();
	}

	void Canvas::updateVBOData(const uint64_t aShapeId, const Shape& aShapeData) noexcept {
		this->mWindow.BindContext();

		this->mVBOData = (GLfloat*)glMapNamedBuffer(this->mWindow.glVBO.GetHandle(), GL_READ_WRITE);

		//attributes for all vertices
		//(x) * 2 - 1 converts [0, 1] UV to [-1, 1]
		//normally OpenGL has Y = 0 at the bottom, we flip! (also we subtract Y instead of adding it)
		for (uint8_t i = 0; i < 4; i++) {
			//positions
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 0] = (((float(aShapeData.mX) + ((i == 1 || i == 2) ? aShapeData.mSizeX : 0.0)) / this->mWindow.SizeX()) * 2.0) - 1.0;
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 1] = (((float(this->mWindow.SizeY() - aShapeData.mY) - ((i == 2 || i == 3) ? aShapeData.mSizeY : 0.0)) / this->mWindow.SizeY()) * 2.0) - 1.0;
			//top left							
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 2] = ((float(aShapeData.mX) / this->mWindow.SizeX()) * 2.0) - 1.0;
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 3] = ((float(this->mWindow.SizeY() - aShapeData.mY) / this->mWindow.SizeY()) * 2.0) - 1.0;
			//size										
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 4] = float(aShapeData.mSizeX) / float(this->mWindow.SizeX());
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 5] = float(aShapeData.mSizeY) / float(this->mWindow.SizeY());
			//outer opacity								
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 6] = float(!aShapeData.mUsesRoundedShader);
			//color					 				
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 7] =  aShapeData.mColor.R;
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 8] =  aShapeData.mColor.G;
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 9] =  aShapeData.mColor.B;
			this->mVBOData[(aShapeId * 4 + i) * csVertexSize + 10] = 1.0f;
		}

		glUnmapNamedBuffer(this->mWindow.glVBO.GetHandle());
		this->mVBOData = nullptr;
	}
	void Canvas::eraseVBOData(const uint64_t aShapeId) noexcept {
		this->mWindow.BindContext();
		this->mVBOData = (GLfloat*)glMapNamedBuffer(this->mWindow.glVBO.GetHandle(), GL_READ_WRITE);

		//move everything 1 step back
		memmove_s(
			&this->mVBOData[aShapeId * csVertexSize * 4], sizeof(float) * csVertexSize * 4 * (csMaxDrawableObjects - aShapeId - 1),  //dest
			&this->mVBOData[(aShapeId + 1) * csVertexSize * 4], sizeof(float) * csVertexSize * 4 * (csMaxDrawableObjects - aShapeId - 1 - 1) //src, -1 as index adjustment and -1 for the now empty spot
		);

		glUnmapNamedBuffer(this->mWindow.glVBO.GetHandle());
		this->mVBOData = nullptr;
	}
}