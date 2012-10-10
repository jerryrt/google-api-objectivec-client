/* Copyright (c) 2012 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
//  GTLCivicInfoElectionsQueryResponse.m
//

// ----------------------------------------------------------------------------
// NOTE: This file is generated from Google APIs Discovery Service.
// Service:
//   Google Civic Information API (civicinfo/us_v1)
// Description:
//   An API for accessing civic information.
// Documentation:
//   https://developers.google.com/civic-information
// Classes:
//   GTLCivicInfoElectionsQueryResponse (0 custom class methods, 2 custom properties)

#import "GTLCivicInfoElectionsQueryResponse.h"

#import "GTLCivicInfoElection.h"

// ----------------------------------------------------------------------------
//
//   GTLCivicInfoElectionsQueryResponse
//

@implementation GTLCivicInfoElectionsQueryResponse
@dynamic elections, kind;

+ (NSDictionary *)arrayPropertyToClassMap {
  NSDictionary *map =
    [NSDictionary dictionaryWithObject:[GTLCivicInfoElection class]
                                forKey:@"elections"];
  return map;
}

+ (void)load {
  [self registerObjectClassForKind:@"civicinfo#electionsQueryResponse"];
}

@end
