#include "Canvas.hpp"

namespace OpenArabTools {
	Shape::Shape() noexcept
		: mX(0), mY(0), mColor(LIGHTCOLOR_BLACK) {}

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
		: Shape(), mSize(10) {}

	void Square::setWidth(const uint64_t aWidth) noexcept {
		this->mSize = aWidth;
	}
	uint64_t Square::getWidth() const noexcept {
		return this->mSize;
	}

	Square::~Square() noexcept {}

	Circle::Circle() noexcept
		: Shape(), mRadius(10) {}

	void Circle::setRadius(const uint64_t aRadius) noexcept {
		this->mRadius = aRadius;
	}
	uint64_t Circle::getRadius() const noexcept {
		return this->mRadius;
	}

	Circle::~Circle() noexcept {}

	Rectangle::Rectangle() noexcept 
		: Shape(), mSizeX(20), mSizeY(10) {}

	void Rectangle::setWidth(const uint64_t aWidth) noexcept {
		this->mSizeX = aWidth;
	}
	void Rectangle::setHeight(const uint64_t aHeight) noexcept {
		this->mSizeY = aHeight;
	}

	uint64_t Rectangle::getWidth() const noexcept {
		return this->mSizeX;
	}
	uint64_t Rectangle::getHeight() const noexcept {
		return this->mSizeY;
	}

	Rectangle::~Rectangle() noexcept {}

	Canvas::Canvas() noexcept {
	
	}
	Canvas::Canvas(const std::string& aTitle) noexcept {

	}
	Canvas::Canvas(const uint64_t aWidth, const uint64_t aHeight, const std::string& aTitle) noexcept {

	}

	uint64_t Canvas::add(const Shape& aShape) noexcept {
		this->mShapes.push_back(aShape);
		return this->mShapes.size() - 1; //id of shape
	}
	void Canvas::remove(const uint64_t aShapeId) noexcept {
		for (uint64_t i = 0; i < this->mShapes.size(); i++) {
			if (i == aShapeId) {
				this->mShapes.erase(this->mShapes.begin() + i);
				return;
			}
		}
	}
	void Canvas::clear() noexcept {
		this->mShapes.clear();
		this->update();
	}

	void Canvas::setBackground() noexcept {

	}

	void Canvas::paint() noexcept {
		this->update();
	}

	bool Canvas::open() const noexcept {
		return this->mWindow.IsWindowOpen();
	}
	bool Canvas::update() noexcept {
		this->mWindow.BindContext();
		this->mWindow.BindShader();

		this->mWindow.glIBO.Draw();

		this->mWindow.Process();
		return this->mWindow.IsWindowOpen();
	}
	void Canvas::run() noexcept {
		while (this->open()) { this->run(); }
	}

	void Canvas::showWindow() noexcept {
		this->mWindow.ShowWindow();
	}
	void Canvas::hideWindow() noexcept {
		this->mWindow.HideWindow();
	}

	void Canvas::setColor() noexcept {
	
	}

	void Canvas::setTitle(const std::string& aTitle) noexcept {
		this->mWindow.SetTitle(aTitle.c_str());
	}

	void Canvas::set(const uint64_t aWidth, const uint64_t aHeight, const std::string& aTitle) noexcept {

	}
	void Canvas::reset() noexcept {

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
	
	}
}