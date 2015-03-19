/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/03
*/
#ifndef __BOUNDINGBoxMANAGER_H_
#define __BOUNDINGBoxMANAGER_H_

#include "BoundingBoxClass.h"

//System Class
class BoundingBoxManager
{
	int m_nBoxs; //number of elements in the list
	std::vector<BoundingBoxClass*> m_lBox; //list of Boxs
	std::vector<matrix4> m_lMatrix; //list of Global spaces of each Box in the list
	std::vector<vector3> m_lColor; //list of colors of each Box in the list
	static BoundingBoxManager* m_pInstance; //  pointer
	float minX, maxX, minY, maxY, minZ, maxZ; // Min and Max points on the object, used for collisions
	
public:
	/* Gets/Constructs the  pointer */
	static BoundingBoxManager* GetInstance();
	/* Destroys the  */
	static void ReleaseInstance(void);

	/* Asks the  for the number of elements in the list */
	int GetBoxTotal(void);

	/*
	GenerateBoundingBox
		Generates a bounding Box from the specified instance name and adds it to the list
	*/
	void GenerateBoundingBox(String a_sInstanceName);

	/*
	SetBoundingBoxSpace
		Sets the Matrix that represents the global position of the Box specified by instance name
	*/
	void SetBoundingBoxSpace(matrix4 a_mModelToWorld, String a_sInstanceName);

	/*
	IdentifyBox
		Returns the index in which the specified Box is stored in the list
	*/
	int IdentifyBox(String a_sInstanceName);

	/*
	AddBoxToRenderList
		Add the specified instance to the render list, ALL will add all of them at once
	*/
	void AddBoxToRenderList(String a_sInstanceName = "ALL");

	/*
	CalculateCollision
		Calculates the collision among all the Boxs in the list
	*/
	void CalculateCollision(void);

private:
	/* Constructor */
	BoundingBoxManager(void);
	/* Copy Constructor */
	BoundingBoxManager(BoundingBoxManager const& other);
	/* Copy Assignment Operator */
	BoundingBoxManager& operator=(BoundingBoxManager const& other);
	/* Destructor */
	~BoundingBoxManager(void);

	/* Releases the objects memory */
	void Release(void);
	/* Initializates the objects fields */
	void Init(void);
};

#endif __BOUNDINGBoxMANAGER_H_