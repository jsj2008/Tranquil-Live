#import "PolyPrimitive.h"

@interface Sphere : PolyPrimitive
+ (Sphere *)sphereWithRadius:(GLMFloat)aRadius stacks:(int)aStacks slices:(int)aSlices useVBO:(BOOL)aUseVBO;
- (id)initWithRadius:(GLMFloat)aRadius stacks:(int)aStacks slices:(int)aSlices useVBO:(BOOL)aUseVBO;
@end
