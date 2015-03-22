#pragma once
#ifndef _GEOPIPELINE_H
#define _GEOPIPELINE_H

#include "XMatrix.h"
#include "Camera.h"

class GeoPipeline
{
public:
	GeoPipeline()
	{
		scaleTran.scale(1.0f, 1.0f, 1.0f);
		worldTranslateTrans.translate(0.0f, 0.0f, 0.0f);
		rotateTrans.rotate(0.0f, 0.0f, 0.0f);
	}

	void setScale(float xScale, float yScale, float zScale)
	{
		scaleTran.scale(xScale, yScale, zScale);
	}

	void setWorldPos(float x, float y, float z)
	{
		worldTranslateTrans.translate(x, y, z);
	}

	void setRotate(float xRotate, float yRotate, float zRotate)
	{
		rotateTrans.rotate(xRotate, yRotate, zRotate);
	}

	void setPerspectiveProj(float FOV, float width, float height, float zNear, float zFar)
	{
		persProjTrans.persProj(FOV, width, height, zNear, zFar);
	}

	void setCamera(const Vector3f& pos, const Vector3f& target, const Vector3f& up)
	{
		cameraTranslationTrans.translate(-pos.x, -pos.y, -pos.z);
		cameraRotateTrans.camera(target, up);
	}

	void setCamera(Camera *camera)
	{
		float x = camera->getPos().x;
		float y = camera->getPos().y;
		float z = camera->getPos().z;
		cameraTranslationTrans.translate(-x, -y, -z);
		cameraRotateTrans.camera(camera->GetTarget(), camera->GetUp());
	}

	void combineTransMat()
	{
		transformer = persProjTrans * cameraRotateTrans * 
			cameraTranslationTrans * worldTranslateTrans * 
			rotateTrans * scaleTran;
	}

	Mat4x4f *getCombineTransMat()
	{
		combineTransMat();//Do't forget to combine all together
		return &transformer;
	}

	Mat4x4f *getStaticTransMat()
	{
		return &transformer;
	}

private:	
	Mat4x4f scaleTran, rotateTrans, worldTranslateTrans, 
		cameraTranslationTrans, cameraRotateTrans, persProjTrans;
	Mat4x4f transformer;
};

#endif

