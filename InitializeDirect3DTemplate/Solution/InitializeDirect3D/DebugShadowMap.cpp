#include "DebugShadowMap.h"
#include "Game.h"

DebugShadowMap::DebugShadowMap(Game* game) : Entity(game)
{
}

void DebugShadowMap::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;

	//game->GetmCommandList()->SetPipelineState(game->GetPSOs()["debug"].Get());

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

void DebugShadowMap::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = MathHelper::Identity4x4();
	renderer->TexTransform = MathHelper::Identity4x4();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["bricks0"].get();
	renderer->Geo = game->getGeometries()["shapeGeo"].get();
	renderer->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["quad"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["quad"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["quad"].BaseVertexLocation;


	game->mRitemLayer[(int)RenderLayer::Debug].push_back(render.get());
	game->getRenderItems().push_back(std::move(render));
}
