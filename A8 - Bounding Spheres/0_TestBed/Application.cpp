#include "ApplicationClass.h"
void ApplicationClass::InitAppVariables()
{
	float fSteve = 0.0f;
	float fMiddle = 1.5f;
	float fCreeper = 3.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pMeshMngr->LoadModel("Minecraft\\MC_Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Creeper.obj", "Creeper");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Cow.obj", "Cow");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Pig.obj", "Pig");
	m_pMeshMngr->LoadModel("Minecraft\\MC_Zombie.obj", "Zombie");
	//m_pMeshMngr->m_pModelMngr->LoadModelUnthreaded("Minecraft\\MC_Steve.obj", "A");
	pBoundingSphere1 = new BoundingSphereClass();
	pBoundingSphere2 = new BoundingSphereClass();

	m_pBSMngr = BoundingSphereManagerSingleton::GetInstance();
	m_pBBMngr = BoundingBoxManager::GetInstance();

	m_m4Creeper = glm::translate(vector3(3.0f,0.0f,0.0f));

	m_pCamera->SetPosition(vector3(fSteve,1.0f,11.0f));
}
void ApplicationClass::GenerateBoundingSphere(matrix4 a_mModelToWorld, String a_sInstanceName)
{
	if(m_pMeshMngr->IsInstanceCreated(a_sInstanceName))
	{
		static bool bInitialized = false;
		static vector3 vCenterPoint;
		static float fDistance;
		if(!bInitialized)
		{
			std::vector<vector3> lVertices = m_pMeshMngr->m_pModelMngr->GetVertices(a_sInstanceName);
			unsigned int nVertices = lVertices.size();
			vCenterPoint = lVertices[0];
			vector3 v3Max(lVertices[0]);
			vector3 v3Min(lVertices[0]);
			for(unsigned int nVertex = 1; nVertex < nVertices; nVertex++)
			{
				//m_v3Centroid += lVertices[nVertex];
				if(v3Min.x > lVertices[nVertex].x)
					v3Min.x = lVertices[nVertex].x;
				else if(v3Max.x < lVertices[nVertex].x)
					v3Max.x = lVertices[nVertex].x;
			
				if(v3Min.y > lVertices[nVertex].y)
					v3Min.y = lVertices[nVertex].y;
				else if(v3Max.y < lVertices[nVertex].y)
					v3Max.y = lVertices[nVertex].y;

				if(v3Min.z > lVertices[nVertex].z)
					v3Min.z = lVertices[nVertex].z;
				else if(v3Max.z < lVertices[nVertex].z)
					v3Max.z = lVertices[nVertex].z;
			}
			vCenterPoint = (v3Min + v3Max) / 2.0f;

			m_pMeshMngr->AddAxisToQueue(a_mModelToWorld * glm::translate(vCenterPoint));

			fDistance = glm::distance(vCenterPoint, lVertices[0]);
			for(unsigned int nVertex = 1; nVertex < nVertices; nVertex++)
			{
				float fDistanceNew = glm::distance(vCenterPoint, lVertices[nVertex]);
				if(fDistance < fDistanceNew)
					fDistance = fDistanceNew;
			}

			bInitialized = true;
		}
		m_pMeshMngr->AddSphereToQueue(a_mModelToWorld * glm::translate(vCenterPoint) * glm::scale(vector3(fDistance * 2.0f)), MERED, MERENDER::WIRE);
	}
}

void ApplicationClass::GenerateBoundingBox(matrix4 a_mModelToWorld, String a_sInstanceName)
{
	if(m_pMeshMngr->IsInstanceCreated(a_sInstanceName))
	{
		static bool bInitialized = false;
		static vector3 vCenterPoint;
		static float fDistance;
		if(!bInitialized)
		{
			std::vector<vector3> lVertices = m_pMeshMngr->m_pModelMngr->GetVertices(a_sInstanceName);
			unsigned int nVertices = lVertices.size();
			vCenterPoint = lVertices[0];
			vector3 v3Max(lVertices[0]);
			vector3 v3Min(lVertices[0]);
			for(unsigned int nVertex = 1; nVertex < nVertices; nVertex++)
			{
				//m_v3Centroid += lVertices[nVertex];
				if(v3Min.x > lVertices[nVertex].x)
					v3Min.x = lVertices[nVertex].x;
				else if(v3Max.x < lVertices[nVertex].x)
					v3Max.x = lVertices[nVertex].x;
			
				if(v3Min.y > lVertices[nVertex].y)
					v3Min.y = lVertices[nVertex].y;
				else if(v3Max.y < lVertices[nVertex].y)
					v3Max.y = lVertices[nVertex].y;

				if(v3Min.z > lVertices[nVertex].z)
					v3Min.z = lVertices[nVertex].z;
				else if(v3Max.z < lVertices[nVertex].z)
					v3Max.z = lVertices[nVertex].z;
			}
			vCenterPoint = (v3Min + v3Max) / 2.0f;

			m_pMeshMngr->AddAxisToQueue(a_mModelToWorld * glm::translate(vCenterPoint));

			fDistance = glm::distance(vCenterPoint, lVertices[0]);
			for(unsigned int nVertex = 1; nVertex < nVertices; nVertex++)
			{
				float fDistanceNew = glm::distance(vCenterPoint, lVertices[nVertex]);
				if(fDistance < fDistanceNew)
					fDistance = fDistanceNew;
			}

			bInitialized = true;
		}
		m_pMeshMngr->AddSphereToQueue(a_mModelToWorld * glm::translate(vCenterPoint) * glm::scale(vector3(fDistance * 2.0f)), MERED, MERENDER::WIRE);
	}
}

void ApplicationClass::Update (void)
{
	m_pSystem->UpdateTime(); //Update the system

	m_pMeshMngr->Update(); //Updates the mesh information

	float fTimeSpan = m_pSystem->StopClock(); //Check the time difference between this method calls
	static float fRunTime = 0.0f;

	fRunTime += fTimeSpan; //update the run time count
	matrix4 m4Steve = glm::rotate(matrix4(IDENTITY), fRunTime * 15, vector3( 0.0f,-1.0f, 0.0f));
	matrix4 m4Zombie = glm::translate(vector3(-6.0f, 0.0f, 0.0f));
	matrix4 m4Cow = glm::translate(vector3(-3.0f, 0.0f, 0.0f));
	matrix4 m4Pig = glm::translate(vector3(6.0f, 0.0f, 0.0f));
	
	m_pMeshMngr->SetModelMatrix(m4Steve, "Steve");
	m_pMeshMngr->SetModelMatrix(m_m4Creeper, "Creeper");
	m_pMeshMngr->SetModelMatrix(m4Pig, "Pig");
	m_pMeshMngr->SetModelMatrix(m4Zombie, "Zombie");
	m_pMeshMngr->SetModelMatrix(m4Cow, "Cow");

#pragma region Method
	//GenerateBoundingSphere(mA,"A");
#pragma endregion

#pragma region Bounding Sphere Class
	//pBoundingSphere1->GenerateBoundingSphere("Steve");
	//pBoundingSphere2->GenerateBoundingSphere("Creeper");
	
	//pBoundingSphere1->AddSphereToRenderList(m4Steve, MEYELLOW, true);
	//pBoundingSphere2->AddSphereToRenderList(m_m4Creeper, MEYELLOW, true);
#pragma endregion

#pragma region Bounding Sphere Manager
	m_pBSMngr->GenerateBoundingSphere("Steve");
	m_pBSMngr->GenerateBoundingSphere("Creeper");
	m_pBSMngr->GenerateBoundingSphere("Cow");
	m_pBSMngr->GenerateBoundingSphere("Zombie");
	m_pBSMngr->GenerateBoundingSphere("Pig");

	m_pBSMngr->SetBoundingSphereSpace(m4Steve, "Steve");
	m_pBSMngr->SetBoundingSphereSpace(m_m4Creeper, "Creeper");
	m_pBSMngr->SetBoundingSphereSpace(m4Cow, "Cow");
	m_pBSMngr->SetBoundingSphereSpace(m4Pig, "Pig");
	m_pBSMngr->SetBoundingSphereSpace(m4Zombie, "Zombie");

	m_pBSMngr->CalculateCollision();

	m_pBSMngr->AddSphereToRenderList("ALL");

	m_pBBMngr->GenerateBoundingBox("Steve");
	m_pBBMngr->GenerateBoundingBox("Creeper");
	m_pBBMngr->GenerateBoundingBox("Cow");
	m_pBBMngr->GenerateBoundingBox("Zombie");
	m_pBBMngr->GenerateBoundingBox("Pig");

	m_pBBMngr->SetBoundingBoxSpace(m4Steve, "Steve");
	m_pBBMngr->SetBoundingBoxSpace(m_m4Creeper, "Creeper");
	m_pBBMngr->SetBoundingBoxSpace(m4Cow, "Cow");
	m_pBBMngr->SetBoundingBoxSpace(m4Pig, "Pig");
	m_pBBMngr->SetBoundingBoxSpace(m4Zombie, "Zombie");

	m_pBBMngr->CalculateCollision();

	//m_pBBMngr->AddBoxToRenderList("ALL");
#pragma endregion

	m_pMeshMngr->AddInstanceToRenderList();
	
	//First person camera movement
	if(m_bFPC == true)
		CameraRotation();

	m_pCamera->PrintInfo();

	printf("FPS: %d\r", m_pSystem->FPS);//print the Frames per Second
}
void ApplicationClass::Display (void) //for OpenGL 3.X Applications
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear the window

	//m_pGrid->Render(100.0f); //renders the grid with a 100 scale

	m_pMeshMngr->Render();

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}