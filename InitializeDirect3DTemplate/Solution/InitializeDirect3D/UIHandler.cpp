#include "UIHandler.h"
#include "Game.h"
UIHandler::UIHandler(UIHandlerType type, Game* game) : Entity(game), mType(type)
{
	switch (type)
	{
	case (PressAnyKey):
		mSprite = "PressAnyKey";
		break;
	case (MainMenu):
		mSprite = "bricks0";
		break;
	default:
		mSprite = "PressAnyKey";
		break;
	}
}
void UIHandler::drawCurrent()const
{
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
void  UIHandler::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["shapeGeo"].get();
	renderer->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->mRitemLayer[(int)RenderLayer::Opaque].push_back(render.get());
	game->getRenderItems().push_back(std::move(render));
}