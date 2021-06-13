#include "PTPAppDelegate.h"
#include "cocos2d.h"
#include "PTPConfig.h"
#include "models/PTModelController.h"
#include "PTPSettingsController.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "models/PTModelScreen.h"
#include "models/PTModelAtlas.h"
#include "models/PTModelGeneralSettings.h"
#include "models/objects/PTModelAssetCharacter.h"
#include "models/objects/PTModelObjectAssetTrail.h"
#include "models/objects/PTModelObjectAssetFlag.h"
#include "models/objects/PTModelObjectButtonPurchase.h"


#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved){
    JniHelper::setJavaVM(vm);
    return JNI_VERSION_1_4;
}

void Java_com_secrethq_utils_PTJniHelper_loadModelController(JNIEnv*  env, jobject thiz){
        PTLog("start laoding XML");

        PTModelController *mc = PTModelController::shared();
        while (!mc->loadDirectory("data"));

        PTLog("end loading XML");
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h){
    PTModelController *mc = PTModelController::shared();
    if (!CCDirector::sharedDirector()->getOpenGLView()){
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);
        
        //loading general info 
        mc->clean();
        mc->loadFile( "data/PTModelGeneralSettings.0.attributes.xml", PTModelController::Attributes );
        mc->loadFile( "data/PTModelFont.0.attributes.xml", PTModelController::Attributes );     
        mc->loadFile( "data/PTModelScreen.0.attributes.xml", PTModelController::Attributes );
        mc->loadFile( "data/PTModelObjectLabel.0.attributes.xml", PTModelController::Attributes );
        mc->loadFile( "data/PTModelObjectLoadingBar.0.attributes.xml", PTModelController::Attributes );
        mc->loadFile( "data/PTModelScreen.0.connections.xml", PTModelController::Connections );

        PTPAppDelegate *pAppDelegate = new PTPAppDelegate();
        CCApplication::sharedApplication()->run();

        //clean up main model controller before starting loading Objects form XML files
        mc->clean();


    }
    else {
        PTLog("NATIVE RE INIT");
        ccGLInvalidateStateCache();        
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        ccDrawInit();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 

    }
}

}
