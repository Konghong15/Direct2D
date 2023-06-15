#pragma once

namespace gameProcessor
{
	class FactoryResource
	{
	public:
		FactoryResource() = default;
		virtual ~FactoryResource() = 0;

		inline unsigned int AddRef();
		inline unsigned int Release();

	private:
		unsigned int mRefCount = 1;
	};

	unsigned int FactoryResource::AddRef()
	{
		return ++mRefCount;
	}

	unsigned int FactoryResource::Release()
	{
		if (--mRefCount == 0)
		{
			delete this;
			
			return 0;
		}

		return mRefCount;
	}
}