#pragma once
#include "GLBaseImplementation.hpp"

namespace OpenArabTools {
	namespace Internal {
		class OPENARABTOOLS_OBJ BatchRenderer {
		public:
			BatchRenderer() noexcept;

			~BatchRenderer() noexcept;
		private:
			GLVertexBuffer mVBOCircle;
			GLIndexBuffer  mIBOCircle;

			//for squares -> backgrounds of circles
			GLVertexBuffer mVBOSquare;
			GLIndexBuffer  mIBOSquare;
		};
	}
}