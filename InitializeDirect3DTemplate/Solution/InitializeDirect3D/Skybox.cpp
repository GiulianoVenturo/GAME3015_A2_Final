#include "Skybox.h"
#include "Game.h"

Skybox::Skybox(Game* game) : Entity(game)
{
}

void Skybox::drawCurrent() const
{
	renderer->World = getTransform();
	renderer->NumFramesDirty++;

	game->GetmCommandList()->SetPipelineState(game->GetPSOs()["sky"].Get());

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

void Skybox::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()["sky"].get();
	renderer->Geo = game->getGeometries()["shapeGeo"].get();
	renderer->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["sphere"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["sphere"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["sphere"].BaseVertexLocation;


	game->mRitemLayer[(int)RenderLayer::Sky].push_back(render.get());
	game->getRenderItems().push_back(std::move(render));
}
