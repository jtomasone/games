#include "JCTFBXSkeleton.h"
//Use the Rest Pose
JCTFBXSkeleton::JCTFBXSkeleton(const string &name) : JCTTree(name), JCTFBXBone(name)
{
   this->setType(JCTFBX_SKELETON);
}

JCTFBXSkeleton::JCTFBXSkeleton(void) : JCTTree("ROOT")
{
}

JCTFBXSkeleton::~JCTFBXSkeleton(void)
{
}

void JCTFBXSkeleton::Render()
{
};
