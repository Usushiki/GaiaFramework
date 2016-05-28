//----------------------------------------------------------------//
//					      Direct3D.cpp							�@//		
//																  //
//					  About 		DirectX�N���X�̃\�[�X		�@//
//     	  		    Last Update  2015/07/13						  //
//																  //
//                    Coded by Y.Takada							  //
//																�@//
//----------------------------------------------------------------//




//-----------------------------
//�w�b�_�t�@�C���̃C���N���[�h
//-----------------------------
#include<DirectXColors.h>
#include"Direct3D.hpp"





//-----------------------------
//���C�u���������N
//-----------------------------
#pragma comment(lib,"d3d11.lib")		//DirectX11���C�u����	

#pragma comment(lib,"DirectXTK.lib")	//DirectXTK���C�u����


namespace Gaia
{

	//----------------------------------------
	//!@brief Drect3D�N���X�̎����̏ڍ�
	//----------------------------------------
	class Direct3D::pImpl
	{
		//�����o�ϐ�
	public:

		HWND m_hWindow;												//�E�B���h�E�n���h��


		ComPtr<ID3D11Device>			m_pd3dDevice;				//DirectX11�̃f�o�C�X
		ComPtr<ID3D11DeviceContext>		m_pd3dImmeidiateContext;	//�R���e�L�X�g
		ComPtr<IDXGISwapChain>			m_pSwapChain;				//�X���b�v�`�F�[��
		ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;		//�����_�[�^�[�Q�b�g�r���[
		ComPtr<ID3D11Texture2D>			m_pDepthStencil;			//�[�x�X�e���V��
		ComPtr<ID3D11DepthStencilView>	m_pDepthStencilView;		//�[�x�X�e���V���r���[


		UINT m_RenderTargetWidth;									//�����_�[�^�[�Q�b�g��
		UINT m_RenderTargetHeight;									//�����_�[�^�[�Q�b�g�̍���

	public:

		//-----------------------------
		//!@brief �R���X�g���N�^
		//-----------------------------
		pImpl()
			:m_hWindow(nullptr)
			, m_pd3dDevice(nullptr)
			, m_pd3dImmeidiateContext(nullptr)
			, m_pSwapChain(nullptr)
			, m_pRenderTargetView(nullptr)
			, m_pDepthStencilView(nullptr)
			, m_pDepthStencil(nullptr)
			, m_RenderTargetHeight(0)
			, m_RenderTargetWidth(0)
		{

		}

		//-----------------------------
		//!@brief �f�X�g���N�^
		//-----------------------------
		~pImpl() = default;

	public:
		//----------------------------------------
		//!@brief �f�o�C�X���\�[�X�̍쐬
		//
		//!@param[in] �Ȃ�
		//
		//!@retval    S_OK   ����
		//!@retval    E_FAIL ���s
		//----------------------------------------
		HRESULT CreateDeviceResources()
		{
			UINT createDeviceFlag = 0;

			HRESULT hr = S_OK;


#ifdef _DEBUG
			createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;	//�f�o�b�O���C���[���T�|�[�g����t���O
#endif

			D3D_DRIVER_TYPE DriverTypes[] =
			{
				D3D_DRIVER_TYPE_HARDWARE,
				D3D_DRIVER_TYPE_WARP,
				D3D_DRIVER_TYPE_REFERENCE,
			};

			UINT numDriverTypes = ARRAYSIZE(DriverTypes);


			D3D_FEATURE_LEVEL FeatureLevels[] =
			{
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1,
			};

			D3D_FEATURE_LEVEL featureLevel;


			UINT numFeatureLevel = ARRAYSIZE(FeatureLevels);


			//�f�o�C�X�ƃf�o�C�X�R���e�L�X�g���쐬
			D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				createDeviceFlag,
				FeatureLevels,
				ARRAYSIZE(FeatureLevels),
				D3D11_SDK_VERSION,
				&m_pd3dDevice,
				&featureLevel,
				&m_pd3dImmeidiateContext
			);

			//�N���C�A���g�̈�̎擾
			RECT rc;

			GetClientRect(m_hWindow, &rc);

			m_RenderTargetWidth = rc.right - rc.left;
			m_RenderTargetHeight = rc.bottom - rc.top;


			//�X���b�v�`�F�[��
			hr = CreateSwapChain();
			if (FAILED(hr)) {
				return hr;
			}

			//�o�b�N�o�b�t�@�Ɛ[�x�X�e���V���r���[���쐬
			hr = CreateBackBufferDepthStencil();
			if (FAILED(hr)) {
				return hr;
			}


			return S_OK;
		}

		//----------------------------------------
		//!@brief �X���b�v�`�F�[���̍쐬
		//
		//!@param[in] �Ȃ�
		//
		//!@retval    S_OK   ����
		//!@retval    E_FAIL ���s
		//----------------------------------------
		HRESULT CreateSwapChain()
		{
			HRESULT hr = S_OK;

			// �X���b�v�`�F�[���̐ݒ�
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount = 1;
			sd.BufferDesc.Width = m_RenderTargetWidth;
			sd.BufferDesc.Height = m_RenderTargetHeight;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 0;	//���t���b�V�����[�g��DXGI�̎����ݒ�ɔC����
			sd.BufferDesc.RefreshRate.Denominator = 0;
			sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = m_hWindow;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.Windowed = TRUE;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //�t���X�N���[���ւ̐؂�ւ��̎��ɕ\�����[�h��ύX����

															   //Alt+Enter�ŉ�ʃ��[�h��ύX���Ȃ��悤�ɂ���
			ComPtr<IDXGIDevice1> pDXGIDevice;
			ComPtr<IDXGIAdapter> pDXGIAdapter;
			ComPtr<IDXGIFactory> pDXGIFactory;


			//�C���^�[�t�F�[�X�擾
			hr = m_pd3dDevice.As(&pDXGIDevice);
			if (FAILED(hr)) {
				return hr;
			}

			//�A�_�v�^�[�擾
			hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);
			if (FAILED(hr)) {
				return hr;
			}

			//�t�@�N�g���[�擾
			hr = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (LPVOID*)&pDXGIFactory);
			if (FAILED(hr)) {
				return hr;
			}

			//�X���b�v�`�F�[���̍쐬
			pDXGIFactory->CreateSwapChain(m_pd3dDevice.Get(), &sd, &m_pSwapChain);
			if (FAILED(hr)) {
				return hr;
			}

			//�t���X�N���[���̕s��C���̂��߂Ƀo�b�t�@�����T�C�Y
			m_pSwapChain->ResizeBuffers(sd.BufferCount, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);


			return S_OK;
		}

		
		//-------------------------------------------------------
		//!@brief �o�b�N�o�b�t�@�Ɛ[�x�X�e���V���r���[�̍쐬
		//
		//!@param[in] �Ȃ�
		//
		//!@retval    S_OK   ����
		//!@retval    E_FAIL ���s
		//-------------------------------------------------------
		HRESULT CreateBackBufferDepthStencil()
		{
			HRESULT hr = S_OK;

			////////////////////////
			//�o�b�N�o�b�t�@�̍쐬//
			////////////////////////
			ID3D11Texture2D* pBackBuffer = nullptr;
			hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			if (FAILED(hr)) {
				return hr;
			}

			//�o�b�N�o�b�t�@�Ɏw�肳��Ă���e�N�X�`�������擾
			D3D11_TEXTURE2D_DESC descBackBuffer;
			pBackBuffer->GetDesc(&descBackBuffer);


			//�����_�[�^�[�Q�b�g�r���[���쐬
			hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, m_pRenderTargetView.GetAddressOf());
			pBackBuffer->Release();
			if (FAILED(hr)) {
				return hr;
			}


			//////////////////////
			//�[�x�o�b�t�@�̍쐬//
			//////////////////////


			//�[�x�X�e���V���e�N�X�`���̍쐬
			//�o�b�N�o�b�t�@�Ɏw�肳�ꂽ�e�N�X�`���������Ƃɍ쐬
			CD3D11_TEXTURE2D_DESC descDepth(descBackBuffer);

			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			descDepth.Usage = D3D11_USAGE_DEFAULT;
			descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;
			hr = m_pd3dDevice->CreateTexture2D(&descDepth, nullptr, &m_pDepthStencil);
			if (FAILED(hr)) {
				return hr;
			}


			//�[�x�X�e���V���r���[�̍쐬
			CD3D11_DEPTH_STENCIL_VIEW_DESC descDSV(D3D11_DSV_DIMENSION_TEXTURE2D, descDepth.Format);
			hr = m_pd3dDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &descDSV, &m_pDepthStencilView);
			if (FAILED(hr)) {
				return hr;
			}

			////////////////////////////
			//�����_�[�^�[�Q�b�g�̐ݒ�//
			////////////////////////////
			m_pd3dImmeidiateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());


			//////////////////////////
			//�@�r���[�|�[�g�̍쐬�@//
			//////////////////////////
			CD3D11_VIEWPORT vp(0.0f, 0.0f, (FLOAT)m_RenderTargetWidth, (FLOAT)m_RenderTargetHeight);
			m_pd3dImmeidiateContext->RSSetViewports(1, &vp);

			return S_OK;
		}

		
		//----------------------------------------
		//!@brief ����������
		//
		//!@param[in] _hWindow �E�B���h�E�n���h��
		//
		//!@retval    S_OK   ����
		//!@retval    E_FAIL ���s
		//----------------------------------------
		HRESULT Initialize(HWND _hWindow)
		{
			m_hWindow = _hWindow;

			if (FAILED(CreateDeviceResources()))
			{
				return E_FAIL;
			}

			//�������ɐ���
			return S_OK;
		}

		//--------------------------------------------------------------
		//!@brief		�X�N���[�����[�h�̐ݒ�							
		//																
		//!@param[in]	�X�N���[�����[�h  �@true		�t���X�N���[��	
		//!@param[in]				 �@�@�@ false     �E�B���h�E���[�h	
		//																
		//!@retval       �Ȃ�											
		//--------------------------------------------------------------
		HRESULT SetScreenMode(bool _screenMode)
		{
			return m_pSwapChain->SetFullscreenState(_screenMode,nullptr);
		}
	};
}

namespace Gaia 
{


	//-----------------------------
	//!@brief �R���X�g���N�^
	//-----------------------------
	Direct3D::Direct3D()
		:m_pImpl(std::make_unique<pImpl>())
	{

	}

	//-----------------------------
	//!@brief �f�X�g���N�^
	//-----------------------------
	Direct3D::~Direct3D() = default;
	

	//-------------------------------------------------------
	//!@brief		�f�o�C�X�̎擾							
	//														
	//!@param[in]	�Ȃ�									
	//														
	//!@retval  	�f�o�C�X�̃|�C���^						
	//-------------------------------------------------------
	ID3D11Device* Direct3D::GetDevice() const
	{
		return m_pImpl->m_pd3dDevice.Get();
	}



	//-------------------------------------------------------
	//!@brief		�f�o�C�X�R���e�L�X�g�̎擾				
	//														
	//!@param[in]	�Ȃ�									
	//														
	//!@retval   	�f�o�C�X�R���e�L�X�g�̃|�C���^		
	//-------------------------------------------------------
	ID3D11DeviceContext* Direct3D::GetDeviceContext() const
	{
		return m_pImpl->m_pd3dImmeidiateContext.Get();
	}

	//-------------------------------------------------------
	//!@brief		�X���b�v�`�F�[���̎擾				
	//																	
	//!@param[in]	�Ȃ�										
	//																	
	//!@retval   	�X���b�v�`�F�[���̃|�C���^	
	//-------------------------------------------------------
	IDXGISwapChain* Direct3D::GetSwapChain() const
	{
		return m_pImpl->m_pSwapChain.Get();
	}

	//-------------------------------------------------------
	//!@brief		�����_�[�^�[�Q�b�g�r���[�̎擾			
	//														
	//!@param[in]	�Ȃ�									
	//														
	//!@retval   	�����_�[�^�[�Q�b�g�r���[�̃|�C���^	
	//-------------------------------------------------------
	ID3D11RenderTargetView* Direct3D::GetRenderTargetView() const
	{
		return m_pImpl->m_pRenderTargetView.Get();
	}

	//-------------------------------------------------------
	//!@brief		�����_�[�^�[�Q�b�g�r���[�̎擾			
	//														
	//!@param[in]	�Ȃ�									
	//														
	//!@retval   	�[�x�X�e���V���r���[�̃|�C���^		
	//-------------------------------------------------------
	ID3D11DepthStencilView* Direct3D::GetDepthStencilView() const
	{
		return m_pImpl->m_pDepthStencilView.Get();
	}


	//-------------------------------------------------------
	//!@brief		�X�N���[�����[�h�̐ݒ�
	//														
	//!@param[in]	true		�t���X�N���[��	
	//				false     �@�E�B���h�E���[�h
	//
	//!@retval		�Ȃ�   				
	//-------------------------------------------------------
	HRESULT Direct3D::SetScreenMode(bool isFullScreen)
	{
		return m_pImpl->SetScreenMode(isFullScreen);
	}


}

namespace Gaia
{
	//-------------------------------------------------------
	//!@brief			�t�@�N�g�����\�b�h	
	//															
	//!@param[in] hWindow  �E�B���h�E�n���h��				
	//														
	//!@retval      �������ꂽ�I�u�W�F�N�g�̃|�C���^
	//
	//!@note		Direct3D�̃I�u�W�F�N�g�𐶐�����
	//-------------------------------------------------------
	Direct3D* Direct3D::Create(HWND hWindow)
	{
		//�I�u�W�F�N�g����
		Direct3D* pDirect3D = new Direct3D();

		if (!pDirect3D)
		{
			return nullptr;
		}

		//������
		if (FAILED(pDirect3D->m_pImpl->Initialize(hWindow)))
		{
			pDirect3D->m_pImpl->m_pd3dImmeidiateContext->ClearState();

			delete pDirect3D;

			return nullptr;
		}

		//�I�u�W�F�N�g�̐����ɐ���
		return pDirect3D;
	}
}
