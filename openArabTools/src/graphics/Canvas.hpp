#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	//Forward declaration
	class OPENARABTOOLS_OBJ Canvas;

	struct OPENARABTOOLS_OBJ Shape {
	public:
		Shape() noexcept;

		void setX(const uint64_t aX) noexcept;
		void setY(const uint64_t aY) noexcept;
		void setPosition(const uint64_t aX, const uint64_t aY) noexcept;

		void setColor(const LightColor& aColor) noexcept;
		void resetColor() noexcept;

		uint64_t getX() const noexcept;
		uint64_t getY() const noexcept;
		LightColor getColor() const noexcept;

		virtual ~Shape() noexcept;
	protected:
		uint64_t mX, mY;
		LightColor mColor;
	};

	struct OPENARABTOOLS_OBJ Square : public Shape {
	public:
		Square() noexcept;

		void setWidth(const uint64_t aSize) noexcept;
		uint64_t getWidth() const noexcept;

		~Square() noexcept;
	protected:
		uint64_t mSize;
	};
	struct OPENARABTOOLS_OBJ Circle : public Shape {
	public:
		Circle() noexcept;

		void setRadius(const uint64_t aRadius) noexcept;
		uint64_t getRadius() const noexcept;

		~Circle() noexcept;
	protected:
		uint64_t mRadius;
	};
	//OpenArabTools extension, not in original
	struct OPENARABTOOLS_OBJ Rectangle : public Shape {
	public:
		Rectangle() noexcept;

		void setWidth(const uint64_t aWidth) noexcept;
		void setHeight(const uint64_t aHeight) noexcept;

		uint64_t getWidth() const noexcept;
		uint64_t getHeight() const noexcept;

		~Rectangle() noexcept;
	protected:
		uint64_t mSizeX, mSizeY;
	};

	//A canvas, possible to draw filled-in Squares and Circles
	class OPENARABTOOLS_OBJ Canvas {
	public:
		Canvas() noexcept;
		Canvas(const std::string& aTitle) noexcept;
		Canvas(const uint64_t aWidth, const uint64_t aHeight, const std::string& aTitle) noexcept;

		uint64_t add(const Shape& aShape) noexcept; //returns shape id
		void remove(const uint64_t aShapeId) noexcept;
		void clear() noexcept;

		void setBackground() noexcept;

		//Same as update()
		void paint() noexcept;

		//
		// OpenArabTools necessities
		//

		bool open() const noexcept;
		bool update() noexcept;
		void run() noexcept;

		//
		// OpenArabTools extensions
		//

		void showWindow() noexcept;
		void hideWindow() noexcept;

		void setColor() noexcept;
		void setTitle(const std::string& aTitle) noexcept;

		void set(const uint64_t aWidth, const uint64_t aHeight, const std::string& aTitle) noexcept;
		void reset() noexcept;

		void showWindowAndRun() noexcept;
		bool sleep(const uint64_t aMs) noexcept;

		~Canvas() noexcept;
	private:
		Internal::GLPassthroughWindow mWindow;
		std::vector<Shape> mShapes;
		LightColor mFG, mBG;
	};
}