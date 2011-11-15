/* Copyright (c) 2011 Google Inc.
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
//  GTLObject.h
//


#import <Foundation/Foundation.h>

#import "GTLDefines.h"
#import "GTLUtilities.h"
#import "GTLDateTime.h"

#undef _EXTERN
#undef _INITIALIZE_AS
#ifdef GTLOBJECT_DEFINE_GLOBALS
#define _EXTERN
#define _INITIALIZE_AS(x) =x
#else
#define _EXTERN extern
#define _INITIALIZE_AS(x)
#endif

@interface GTLObject : NSObject <NSCopying> {

 @private

  NSMutableDictionary *json_;

  // Used when creating the subobjects from this one.
  NSDictionary *surrogates_;
  
  // Any complex object hung off this object goes into the cache so the
  // next fetch will get the same object back instead of having to recreate
  // it.
  NSMutableDictionary *childCache_;

  // Anything defined by the client; retained but not used internally; not
  // copied by copyWithZone:
  NSMutableDictionary *userProperties_;
}

@property (nonatomic, retain) NSMutableDictionary *JSON;
@property (nonatomic, retain) NSDictionary *surrogates;
@property (nonatomic, retain) NSMutableDictionary *userProperties;

///////////////////////////////////////////////////////////////////////////////
//
// Public methods
//
// These methods are intended for users of the library
//

+ (id)object;
+ (id)objectWithJSON:(NSMutableDictionary *)dict;

- (id)copyWithZone:(NSZone *)zone;

- (NSString *)JSONString;

// generic access to json; also creates it if necessary
- (void)setJSONValue:(id)obj forKey:(NSString *)key;
- (id)JSONValueForKey:(NSString *)key;

// Returns the list of keys in this object's JSON that aren't listed as
// properties on the object.
- (NSArray *)additionalJSONKeys;

// Any keys in the JSON that aren't listed as @properties on the object
// are counted as "additional properties".  These allow you to get/set them.
- (id)additionalPropertyForName:(NSString *)name;
- (void)setAdditionalProperty:(id)obj forName:(NSString *)name;
- (NSDictionary *)additionalProperties;

// User properties are supported for client convenience, but are not copied by
// copyWithZone.  User Properties keys beginning with _ are reserved by the library.
- (void)setProperty:(id)obj forKey:(NSString *)key; // pass nil obj to remove property
- (id)propertyForKey:(NSString *)key;

// userData is stored as a property with key "_userData"
- (void)setUserData:(id)obj;
- (id)userData;

// Makes a partial query-compatible string describing the fields present
// in this object. (Note: only the first element of any array is examined.)
//
// http://code.google.com/apis/tasks/v1/performance.html#partial
//
- (NSString *)fieldsDescription;

// Makes an object containing only the changes needed to do a partial update
// (patch), where the patch would be to change an object from the original
// to the receiver, such as
//
// GTLSomeObject *patchObject = [newVersion patchObjectFromOriginal:oldVersion];
//
// http://code.google.com/apis/tasks/v1/performance.html#patch
//
// NOTE: this method returns nil if there are no changes between the original
// and the receiver.
- (id)patchObjectFromOriginal:(GTLObject *)original;

// Method creating a null value to set object properties for patch queries that
// delete fields.  Do not use this except when setting an object property for
// a patch query.
+ (id)nullValue;

///////////////////////////////////////////////////////////////////////////////
//
// Protected methods
//
// These methods are intended for subclasses of GTLObject
//

// class registration ("kind" strings) for subclasses
+ (Class)registeredObjectClassForKind:(NSString *)kind;
+ (void)registerObjectClassForKind:(NSString *)kind;

// creation of objects from a JSON dictionary
+ (GTLObject *)objectForJSON:(NSMutableDictionary *)json
                defaultClass:(Class)defaultClass
                  surrogates:(NSDictionary *)surrogates
               batchClassMap:(NSDictionary *)batchClassMap;

// property-to-key mapping (for JSON keys which are not used as method names)
+ (NSDictionary *)propertyToJSONKeyMap;

// property-to-Class mapping for array properties (to say what is in the array)
+ (NSDictionary *)arrayPropertyToClassMap;

// The default class for additional JSON keys
+ (Class)classForAdditionalProperties;

@end

// Collection objects with an "items" property should derive from GTLCollection
// object.  This provides support for fast object enumeration and the
// itemAtIndex: convenience method.
//
// Subclasses must implement the items method dynamically.
@interface GTLCollectionObject : GTLObject <NSFastEnumeration>

// itemAtIndex: returns nil when the index exceeds the bounds of the items array
- (id)itemAtIndex:(NSUInteger)idx;

@end

@interface GTLCollectionObject (DynamicMethods)
- (NSArray *)items;
@end
