#ifdef __cplusplus
#import "react-native-bikegadget-mainapp.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNBikegadgetMainappSpec.h"

@interface BikegadgetMainapp : NSObject <NativeBikegadgetMainappSpec>
#else
#import <React/RCTBridgeModule.h>

@interface BikegadgetMainapp : NSObject <RCTBridgeModule>
#endif

@end
