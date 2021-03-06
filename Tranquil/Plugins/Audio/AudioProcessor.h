// Processes audio from a specified input device
#import <portaudio.h>

@interface AudioProcessor : NSObject
@property(readonly) BOOL isRunning;
@property(readonly) float *frequencyBands;
@property(readwrite, assign, nonatomic) int numberOfFrequencyBands;
@property(readwrite, assign) float gain, smoothingFactor, minDb;

+ (PaDeviceIndex)deviceIndexForName:(NSString *)aName;

- (BOOL)openDevice:(PaDeviceIndex)aDevice;
- (void)close;

- (void)start;
- (void)stop;

- (void)update;
- (float)magnitudeForBand:(int)aBand;
@end
