#import <OpenGL/gl.h>
#import <TranquilCore/TranquilCore.h>
#import <GLMath/GLMath.h>

@class State;

#ifndef __SCRIPTINGBRIDGE__
typedef union _Vertex_t {
	float f[16];
	struct {
		vec4_t position;
		vec4_t normal;
		vec4_t color;
		vec2_t texCoord;
		GLMFloat size;
		GLMFloat shininess;
	};
} Vertex_t;
#else
typedef struct _Vertex_t {
    vec4_t position;
    vec4_t normal;
    vec4_t color;
    vec2_t texCoord;
    GLMFloat size;
    GLMFloat shininess;
} Vertex_t;
#endif

// This class is necessary because it's currently unsupported to pass a struct directly
// to MacRuby TODO: Fix! this is terrible.
// ONLY FOR INTERNAL USE, WILL BE REMOVED AS SOON AS IT BECOMES UNNECESSARY
@interface VertexWrapper : NSObject
@property(readwrite, copy, nonatomic) Vector4 *pos, *normal, *color;
@property(readwrite, copy, nonatomic) Vector2 *texCoord;
@property(readwrite, assign, nonatomic) float size, shininess;
@end

static __inline__ Vertex_t VertexCreate(vec4_t aPos, vec4_t aNormal, vec2_t aTexCoord, vec4_t aColor, float aSize, float aShininess) {
	Vertex_t out = { .position=aPos, .normal=aNormal, .color=aColor, .texCoord=aTexCoord, .size=aSize, .shininess=aShininess };
	return out;
}

typedef enum {
	kPolyPrimitiveRenderModeTriStrip = GL_TRIANGLE_STRIP,
	kPolyPrimitiveRenderModeTriFan = GL_TRIANGLE_FAN,
	kPolyPrimitiveRenderModeTriList = GL_TRIANGLES,
	kPolyPrimitiveRenderModePoints = GL_POINTS
} PolyPrimitiveRenderMode;

typedef void (^VertexMappingBlock)(NSUInteger aIndex, VertexWrapper *aVertex);

@interface PolyPrimitive : NSObject <SceneObject> {
@public
    State *_state;
}
@property(readonly) GLuint vertexBuffer, indexBuffer;
@property(readwrite, assign, nonatomic) Vertex_t *vertices;
@property(readwrite, assign, nonatomic) GLuint *indices;
@property(readwrite, assign, nonatomic) int vertexCount, vertexCapacity, indexCount, indexCapacity;
@property(readonly) BOOL usesIndices;
@property(readwrite, assign, nonatomic) PolyPrimitiveRenderMode renderMode;
@property(readwrite, retain, nonatomic) State *state;
@property(readonly, nonatomic) BOOL isValid;
@property(readwrite, assign, nonatomic) BOOL useVBO;

- (id)initWithVertexCapacity:(int)aVertexCapacity indexCapacity:(int)aIndexCapacity;

- (void)addVertex:(Vertex_t)aVertex;
- (void)clear;

// Frees the VBOs & data for this primitive. rendering it unusable
- (void)invalidate;

- (void)recomputeNormals:(BOOL)aSmooth;

- (PolyPrimitive *)mapVertices:(VertexMappingBlock)aEnumBlock;
@end

