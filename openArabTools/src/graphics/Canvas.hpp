#pragma once
#include "internal/GLInterface.hpp"

namespace OpenArabTools {
	//Forward declaration
	class OPENARABTOOLS_OBJ Canvas;

	//Base Shape class: possible to daisy-chain methods
	struct OPENARABTOOLS_OBJ Shape {
		friend class OPENARABTOOLS_OBJ Canvas;
	public:
		Shape() noexcept;

#ifndef OPENARABTOOLS_NO_DAISYCHAIN
		virtual Shape& setX(const uint64_t aX) noexcept;
		virtual Shape& setY(const uint64_t aY) noexcept;
		virtual Shape& setPosition(const uint64_t aX, const uint64_t aY) noexcept;

		virtual Shape& setColor(const LightColor& aColor) noexcept;
		virtual Shape& resetColor() noexcept;
#else
		void setX(const uint64_t aX) noexcept;
		void setY(const uint64_t aY) noexcept;
		void setPosition(const uint64_t aX, const uint64_t aY) noexcept;
		
		void setColor(const LightColor& aColor) noexcept;
		void resetColor() noexcept;
#endif

		uint64_t getX() const noexcept;
		uint64_t getY() const noexcept;
		LightColor getColor() const noexcept;

		virtual ~Shape() noexcept;
	protected:
		uint64_t mX, mY;
		uint64_t mSizeX, mSizeY;
		LightColor mColor;
		bool mUsesRoundedShader;
	};

	//Square class: has 1 value for size and values for position
	struct OPENARABTOOLS_OBJ Square : public Shape {
		friend class OPENARABTOOLS_OBJ Canvas;
	public:
		Square() noexcept;

#ifndef OPENARABTOOLS_NO_DAISYCHAIN
		virtual Square& setX(const uint64_t aX) noexcept override;
		virtual Square& setY(const uint64_t aY) noexcept override;
		virtual Square& setPosition(const uint64_t aX, const uint64_t aY) noexcept override;

		virtual Square& setColor(const LightColor& aColor) noexcept override;
		virtual Square& resetColor() noexcept override;
#endif

		Square& setWidth(const uint64_t aSize) noexcept;
		uint64_t getWidth() const noexcept;

		~Square() noexcept;
	protected:
	};
	struct OPENARABTOOLS_OBJ Circle : public Shape {
		friend class OPENARABTOOLS_OBJ Canvas;
	public:
		Circle() noexcept;

#ifndef OPENARABTOOLS_NO_DAISYCHAIN
		virtual Circle& setX(const uint64_t aX) noexcept override;
		virtual Circle& setY(const uint64_t aY) noexcept override;
		virtual Circle& setPosition(const uint64_t aX, const uint64_t aY) noexcept override;

		virtual Circle& setColor(const LightColor& aColor) noexcept override;
		virtual Circle& resetColor() noexcept override;
#endif

		Circle& setRadius(const uint64_t aRadius) noexcept;
		uint64_t getRadius() const noexcept;

		~Circle() noexcept;
	protected:
	};
	//OpenArabTools extension, not in original
	struct OPENARABTOOLS_OBJ Rectangle : public Shape {
		friend class OPENARABTOOLS_OBJ Canvas;
	public:
		Rectangle() noexcept;

#ifndef OPENARABTOOLS_NO_DAISYCHAIN
		virtual Rectangle& setX(const uint64_t aX) noexcept override;
		virtual Rectangle& setY(const uint64_t aY) noexcept override;
		virtual Rectangle& setPosition(const uint64_t aX, const uint64_t aY) noexcept override;

		virtual Rectangle& setColor(const LightColor& aColor) noexcept override;
		virtual Rectangle& resetColor() noexcept override;
#endif

		Rectangle& setWidth(const uint64_t aWidth) noexcept;
		Rectangle& setHeight(const uint64_t aHeight) noexcept;

		uint64_t getWidth() const noexcept;
		uint64_t getHeight() const noexcept;

		~Rectangle() noexcept;
	protected:
	};

	//A canvas, possible to draw filled-in shapes
	class OPENARABTOOLS_OBJ Canvas {
	public:
		Canvas() noexcept;
		Canvas(const std::string& aTitle) noexcept;
		Canvas(const uint64_t aWidth, const uint64_t aHeight, const std::string& aTitle) noexcept;

		Canvas(const Canvas& aOther) noexcept;
		Canvas(Canvas&& aOther) noexcept;
		Canvas& operator=(const Canvas& aOther) noexcept;
		Canvas& operator=(Canvas&& aOther) noexcept;

		uint64_t add(const Shape& aShape) noexcept; //returns shape id
		uint64_t updateShape(const uint64_t aShapeId, const Shape& aNewData) noexcept;
		void remove(const uint64_t aShapeId) noexcept;
		void clear() noexcept;

		void setBackground(const LightColor& aLC) noexcept;

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

		void setTitle(const std::string& aTitle) noexcept;

		void set(const uint64_t aWidth, const uint64_t aHeight, const std::string& aTitle) noexcept;
		void reset() noexcept;

		void showWindowAndRun() noexcept;
		bool sleep(const uint64_t aMs) noexcept;

		~Canvas() noexcept;
	private:
		Internal::GLPassthroughWindow mWindow;
		std::vector<Shape> mShapes;
		GLfloat* mVBOData;
		bool mInit;

		void updateVBOData(const uint64_t aShapeId, const Shape& aShapeData) noexcept;
		void eraseVBOData(const uint64_t aShapeId) noexcept;
	};
}