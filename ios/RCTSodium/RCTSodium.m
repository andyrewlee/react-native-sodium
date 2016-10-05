//
//  RCTSodium.m
//  RCTSodium
//
//  Created by Lyubomir Ivanov on 9/25/16.
//  Copyright © 2016 Lyubomir Ivanov. All rights reserved.
//
#import "RCTBridgeModule.h"
#import "RCTUtils.h"
#import "sodium.h"

#import "RCTSodium.h"

@implementation RCTSodium

static bool isInitialized;

RCT_EXPORT_MODULE();

+ (void) initialize
{
    [super initialize];
    isInitialized = sodium_init() != -1;
}

// *****************************************************************************
// * Sodium-specific functions
// *****************************************************************************
RCT_EXPORT_METHOD(sodium_version_string:(RCTPromiseResolveBlock)resolve reject:(__unused RCTPromiseRejectBlock)reject)
{
    resolve(@(sodium_version_string()));
}


// *****************************************************************************
// * Random data generation
// *****************************************************************************
RCT_EXPORT_METHOD(randombytes_random:(RCTPromiseResolveBlock)resolve reject:(__unused RCTPromiseRejectBlock)reject)
{
    resolve(@(randombytes_random()));
}

RCT_EXPORT_METHOD(randombytes_uniform:(NSUInteger)upper_bound resolve:(RCTPromiseResolveBlock)resolve reject:(__unused RCTPromiseRejectBlock)reject)
{
    resolve(@(randombytes_uniform((uint32_t)upper_bound)));
}

RCT_EXPORT_METHOD(randombytes_buf:(NSUInteger)size resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject)
{
    unsigned char buf[(u_int32_t)size];
    randombytes_buf(buf,(u_int32_t)size);
    NSString *buf64 = [[NSData dataWithBytesNoCopy:buf length:sizeof(buf) freeWhenDone:NO]  base64EncodedStringWithOptions:0];
    resolve(buf64);
}

RCT_EXPORT_METHOD(randombytes_close)
{
    randombytes_close();
}

RCT_EXPORT_METHOD(randombytes_stir)
{
    randombytes_stir();
}



// *****************************************************************************
// * Public-key cryptography - authenticated encryption
// *****************************************************************************
RCT_EXPORT_METHOD(crypto_box_keypair:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject)
{
    unsigned char pk[crypto_box_PUBLICKEYBYTES],sk[crypto_box_PUBLICKEYBYTES];
    int result = crypto_box_keypair(pk,sk);
    if ( result == 0) {
        NSString *pk64 = [[NSData dataWithBytesNoCopy:pk length:sizeof(pk) freeWhenDone:NO]  base64EncodedStringWithOptions:0];
        NSString *sk64 = [[NSData dataWithBytesNoCopy:sk length:sizeof(sk) freeWhenDone:NO]  base64EncodedStringWithOptions:0];
        resolve(@{@"pk":pk64, @"sk":sk64});
    }
    else
        reject(RCTErrorUnspecified, nil, RCTErrorWithMessage(@"Error")); //TODO: return result
}

@end
