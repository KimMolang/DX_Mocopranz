#include "stdafx.h"
#include "FbxParser.h"


//void CFbxParser::ParsingVertex(FbxNode* _pNode,
//								Animation* _pAnimation)
//{
//	std::map<unsigned int, std::vector<unsigned int>> mVertexByIndex;
//	FbxNodeAttribute *pFbxNodeAttribute = _pNode->GetNodeAttribute();
//
//	_pAnimation->pAniBuffer->m_strName = _pNode->GetName();
//
//	if (pFbxNodeAttribute != nullptr && pFbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
//	{
//		//std::cout << "EXIST Attribute in " << _pNode->GetName() << std::endl;
//
//		FbxMesh * pMesh = _pNode->GetMesh();
//
//		//std::cout << "Load Vetex Count...";
//		const unsigned int VertexCount = pMesh->GetControlPointsCount();
//		const unsigned int IndexCount = pMesh->GetPolygonVertexCount();
//		//std::cout << "DONE!" << std::endl;
//
//		//std::cout << "Load Vertex Position...";
//		{
//			FbxVector4 *lVertexArray = new FbxVector4[VertexCount];
//			for (unsigned int i = 0; i < VertexCount; i++)
//				lVertexArray[i] = pMesh->GetControlPoints()[i];
//
//
//			int *IndexArray = new int[IndexCount];
//			for (unsigned int i = 0; i < IndexCount; i++)
//				IndexArray[i] = pMesh->GetPolygonVertices()[i];
//
//			_pAnimation->pAniBuffer->SetVertexSize(IndexCount);
//			for (unsigned int i = 0; i < IndexCount; i++)
//			{
//				/* ���ؽ��� ���� ��ġ ������ �����´�. */
//				_pAnimation->pAniBuffer->GetVertex(i)->SetPos(
//					(float)lVertexArray[IndexArray[i]].mData[0],
//					(float)lVertexArray[IndexArray[i]].mData[1],
//					(float)lVertexArray[IndexArray[i]].mData[2]);
//
//				mVertexByIndex[IndexArray[i]].push_back(i);
//			}
//		}
//		//std::cout << "DONE!" << std::endl;
//
//		//std::cout << "Load Vertex Normal...";
//		FbxArray<FbxVector4> NormalArray;
//		pMesh->GetPolygonVertexNormals(NormalArray);
//
//		for (unsigned int i = 0; i < IndexCount; i++)
//		{
//			/* ���ؽ��� �븻 ��ġ ������ �����´�. */
//			_pAnimation->pAniBuffer->GetVertex(i)->SetNormal(
//				(float)NormalArray[i].mData[0],
//				(float)NormalArray[i].mData[1],
//				(float)NormalArray[i].mData[2]);
//		}
//		//std::cout << "DONE!" << std::endl;
//
//
//		{	// UV���� ����
//			FbxArray<FbxVector2> UVArray;		// UV�� �迭
//			FbxStringList uvNameList;	pMesh->GetUVSetNames(uvNameList);
//			pMesh->GetPolygonVertexUVs(uvNameList.GetStringAt(0), UVArray);
//			for (unsigned int i = 0; i < IndexCount; ++i)
//			{
//				// ���� UV �迭���� i��° ����� ������ �ش� ������ �޽��� i��° ������ �����Ѵ�
//				_pAnimation->pAniBuffer->GetVertex(i)->vTextureUV.x = (float)UVArray[i].mData[0];
//				_pAnimation->pAniBuffer->GetVertex(i)->vTextureUV.y = 1.0f - (float)UVArray[i].mData[1];
//			}
//		}
//
//
//		FbxGeometry * pGeo = _pNode->GetGeometry();
//		int SkinCount = pGeo->GetDeformerCount(FbxDeformer::eSkin);
//		//std::cout << _pNode->GetName() << " ��Ų�� ���� : " << SkinCount << std::endl;
//
//		for (int i = 0; i < SkinCount; i++){
//			FbxSkin * pSkin = (FbxSkin*)pGeo->GetDeformer(i, FbxDeformer::eSkin);
//			int ClusterCount = pSkin->GetClusterCount();
//
//			//std::cout << _pNode->GetName() << " Ŭ�������� ���� : " << ClusterCount << " " << std::endl;
//
//			for (int j = 0; j < ClusterCount; j++)
//			{
//				FbxCluster *pCluster = pSkin->GetCluster(j);
//
//				int ClusterIndexCount = pCluster->GetControlPointIndicesCount();
//				int * ClusterIndices = pCluster->GetControlPointIndices();
//				double * ClusterWeights = pCluster->GetControlPointWeights();
//
//				//std::cout << _pNode->GetName() << " Ŭ������ �ε����� ���� : " << ClusterIndexCount << " " << std::endl;
//				for (int k = 0; k < ClusterIndexCount; k++)
//				{
//					std::string BoneName = std::string(pCluster->GetLink()->GetName());
//
//					int INDEX = _pAnimation->mapIndexByName[BoneName];
//
//					//std::cout<<m_mIndexByName.size()<<std::endl;
//					FbxAMatrix LinkBoneMtx;
//					FbxAMatrix TransBoneMtx;
//
//					FbxAMatrix ResultMatrix;
//
//					pCluster->GetTransformLinkMatrix(LinkBoneMtx);
//					pCluster->GetTransformMatrix(TransBoneMtx);
//
//					ResultMatrix = LinkBoneMtx.Inverse() *  TransBoneMtx;
//
//					for (int m = 0; m < 4; ++m)
//						for (int n = 0; n < 4; ++n)
//							_pAnimation->pBaseBoneMatrix[INDEX].m[m][n] = (float)(ResultMatrix.Get(m, n));
//
//
//					float BoneWeight = (float)ClusterWeights[k];
//					int BoneIndex = ClusterIndices[k];
//
//					for (auto iter : mVertexByIndex[BoneIndex])
//					{
//
//						if (INDEX == 0 || INDEX == -1)
//						{
//
//						}
//						else
//						{
//							_pAnimation->pAniBuffer->m_pVertex[iter].AddBone(INDEX, BoneWeight);
//						}
//					}
//				}
//			}
//		}
//	}
//	else
//	{
//		//std::cout << "NOT EXIST Attribute in " << _pNode->GetName() << std::endl;
//	}
//
//	_pAnimation->pAniBuffer->CreateBuffer();
//
//
//	unsigned int nNodeChild = _pNode->GetChildCount();
//
//	for (unsigned int i = 0; i < nNodeChild; i++)
//	{
//		FbxNode *pChildNode = _pNode->GetChild(i);
//
//		CAniBuffer* pChild = new CAniBuffer;				//�߰��� �ڽ� �Ҵ�
//		_pAnimation->pAniBuffer->AddChild(pChild);							//�ڽ� �߰�
//
//		ParsingVertex(pChildNode, _pAnimation);
//	}
//}
//
//void CFbxParser::ParsingAnimation(FbxNode* _pNode,
//									Animation* _pAnimation,
//									FbxAnimStack* _pAniStatck)
//{
//	//std::cout<<pNode->GetName()<<"\'s Child Count :"<<pNode->GetChildCount()<<std::endl;
//
//	if (_pNode != nullptr)
//	{
//		unsigned int BoneIndex = _pAnimation->mapIndexByName[_pNode->GetName()];	//���� �ε����� �����´�.
//
//		//std::cout << _pNode->GetName() << "(INDEX:" << g_mIndexByName[_pNode->GetName()] << ") Load..." << g_mIndexByName.size() << std::endl;
//
//		{
//			FbxTime maxTime = _pAniStatck->GetLocalTimeSpan().GetDuration();
//			for (long long i = 0; i < maxTime.GetMilliSeconds() / 10; i++)
//			{
//				FbxTime n_time;
//				n_time.SetMilliSeconds(i * 10);
//
//				for (int m = 0; m < 4; ++m)
//				for (int n = 0; n < 4; ++n)
//					_pAnimation->ppAniMatrix[i][BoneIndex].m[m][n] = (float)((_pNode->EvaluateGlobalTransform(n_time)).Get(m, n));
//
//			}
//		}
//	}
//
//	for (int i = 0; i < _pNode->GetChildCount(); ++i)
//		ParsingAnimation(_pNode->GetChild(i), _pAnimation, _pAniStatck);
//}
//
