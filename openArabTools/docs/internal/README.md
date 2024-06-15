# Internal documentation

### Conditional functions (debug only)
- void GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

### Typedefs and public constants
- typedef uint32_t GLHandle;
- constexpr static GLHandle csGLInvalidHandle = INT32_MAX;

### CircleColor
### GLVertexBuffer
### GLIndexBuffer
### GLShaderBuffer

### Buffer helper functions
- void GenerateTileIndices(GLuint** aBuffer, const uint64_t aAmount);
- void ApplyChangesI(GLuint** const aBuffer, const uint64_t aAmount, GLIndexBuffer* const aObject) noexcept;
- *In namespace Debug:*
- void PrintVertexArray(GLfloat** aArray, const uint64_t aAmountOfVertices, const uint64_t aVertexSize, const uint64_t aVertexPrecisionOverride = 2) noexcept;
- void PrintIndexArray(GLuint** aArray, const uint64_t aAmountOfObjects, const uint64_t aIndicesPerObject, const uint64_t aNumberWidthOverride = 4) noexcept;
		
### Shader helper functions

- `[[nodiscard]] GLHandle MakeShader(const char* aVertSource, const char* aFragSource) noexcept;`
- `extern const char* const VertexPassSource;`
- `extern const char* const FragmentPassSource;`
- `extern const char* const VertexCircleSource;`
- `extern const char* const FragmentCircleSource;`

### GLWindow
### GLCircleWindow
### GLPassthroughWindow