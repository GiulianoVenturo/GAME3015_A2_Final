#include "SpriteNode.h"
#include "Game.h"

SpriteNode::SpriteNode(BackgroundType backgroundtype,Game* game) : Entity(game)
{
	
	switch (backgroundtype)
	{
	case (Desert):
		mBackground = "Desert";		
		break;
	case (bricks0):
		mBackground = "bricks0";
		break;
	default:
		mBackground = "Desert";
		break;
	}
}

void SpriteNode::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;

	game->GetmCommandList()->SetPipelineState(game->GetPSOs()["opaque"].Get());

	auto vbv = renderer->Geo->VertexBufferView();
	auto ibv = renderer->Geo->IndexBufferView();

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	auto objectCB = game->GetmCurrFrameResource()->ObjectCB->Resource();


	game->GetmCommandList()->IASetVertexBuffers(0, 1, &vbv);
	game->GetmCommandList()->IASetIndexBuffer(&ibv);
	game->GetmCommandList()->IASetPrimitiveTopology(renderer->PrimitiveType);

	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + renderer->ObjCBIndex * objCBByteSize;

	game->GetmCommandList()->SetGraphicsRootConstantBufferView(0, objCBAddress);
	game->GetmCommandList()->DrawIndexedInstanced(renderer->IndexCount, 1, renderer->StartIndexLocation, renderer->BaseVertexLocation, 0);

}

void SpriteNode::buildCurrent()
{
	//auto render = std::make_unique<RenderItem>();
	//renderer = render.get();
	//renderer->World = getTransform();
	//XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(10.0f, 10.0f, 10.0f));
	//renderer->ObjCBIndex = game->getRenderItems().size();
	//renderer->Mat = game->getMaterials()["Desert"].get();
	//renderer->Geo = game->getGeometries()["shapeGeo"].get();//renderer->Geo = game->getGeometries()["boxGeo"].get();
	//renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	//renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	//renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	//game->getRenderItems().push_back(std::move(render));

	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(10.0f, 10.0f, 10.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mBackground].get();
	renderer->Geo = game->getGeometries()["shapeGeo"].get();
	renderer->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->mRitemLayer[(int)RenderLayer::Opaque].push_back(render.get());
	game->getRenderItems().push_back(std::move(render));
	
}
