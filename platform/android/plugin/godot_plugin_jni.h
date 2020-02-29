/*************************************************************************/
/*  godot_plugin_jni.h                                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef GODOT_PLUGIN_JNI_H
#define GODOT_PLUGIN_JNI_H

#include <android/log.h>
#include <jni.h>

extern "C" {
JNIEXPORT void JNICALL Java_org_godotengine_godot_plugin_GodotPlugin_nativeRegisterSingleton(JNIEnv *env, jclass clazz, jstring name, jobject obj);
JNIEXPORT void JNICALL Java_org_godotengine_godot_plugin_GodotPlugin_nativeRegisterMethod(JNIEnv *env, jclass clazz, jstring sname, jstring name, jstring ret, jobjectArray args);
JNIEXPORT void JNICALL Java_org_godotengine_godot_plugin_GodotPlugin_nativeRegisterSignal(JNIEnv *env, jclass clazz, jstring sname, jstring name, jobjectArray args);
JNIEXPORT void JNICALL Java_org_godotengine_godot_plugin_GodotPlugin_nativeEmitSignal(JNIEnv *env, jclass clazz, jstring sname, jstring name, jobjectArray params);
JNIEXPORT void JNICALL Java_org_godotengine_godot_plugin_GodotPlugin_nativeRegisterGDNativeLibraries(JNIEnv *env, jobject obj, jobjectArray gdnlib_paths);
}

#include "core/engine.h"

class JNISingleton : public Object {

	GDCLASS(JNISingleton, Object);

	struct MethodData {

		jmethodID method;
		Variant::Type ret_type;
		Vector<Variant::Type> argtypes;
	};

	jobject instance;
	Map<StringName, MethodData> method_map;

public:
	virtual Variant call(const StringName &p_method, const Variant **p_args, int p_argcount, Variant::CallError &r_error);

	jobject get_instance() const;
	void set_instance(jobject p_instance);

	void add_method(const StringName &p_name, jmethodID p_method, const Vector<Variant::Type> &p_args, Variant::Type p_ret_type);

    void add_signal(const StringName &p_name, const Vector<Variant::Type> &p_args);

	JNISingleton();
};


#endif // GODOT_PLUGIN_JNI_H
