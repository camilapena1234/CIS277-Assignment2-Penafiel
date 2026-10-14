#include "MemoryPool.h"

MemoryPool::MemoryPool(size_t blockSize, size_t blockCount)
: blockSize_(blockSize),
blockCount_(blockCount),
memory_(nullptr),
allocated_ (nullptr)
{
    memory_ = new char[blockSize * blockCount_];
    allocated_ = new bool[blockCount_];

    for (size_t i = 0; i < blockCount_; ++i)
    {
        allocated_[i] = false;

        void* blockAddress = memory_ + (i * blockSize_);
        freeBlocks_.push(blockAddress);
    }
}

MemoryPool::~MemoryPool()
{
    delete[] memory_;
    delete[] allocated_;
}

void* MemoryPool::allocate()
{
    if (freeBlocks_.empty())
    {
        return nullptr;
    }
    
    void* ptr = freeBlocks_.pop();

    char* bytePtr = static_cast<char*>(ptr);
    size_t index = (bytePtr - memory_) / blockSize_;

    allocated_[index] = true;

    return ptr;
}

bool MemoryPool::deallocate(void* ptr)
{
    if (ptr == nullptr)
    {
        return false;
    }

    char* bytePtr = static_cast<char*>(ptr);

    if (bytePtr < memory_ ||
        bytePtr >= memory_ + (blockSize_ * blockCount_))
    {
        return false;
    }

    size_t offset = bytePtr - memory_;

    if (offset % blockSize_ != 0)
    {
        return false;
    }

    size_t index = offset / blockSize_;

    if (!allocated_[index])
    {
        return false;
    }

    allocated_[index] = false;
    freeBlocks_.push(ptr);

    return true;
}

size_t MemoryPool::availableBlocks() const
{
    return freeBlocks_.size();
}

size_t MemoryPool::allocatedBlocks() const
{
    return blockCount_ - freeBlocks_.size();
}

size_t MemoryPool::blockSize() const
{
    return blockSize_;
}

size_t MemoryPool::capacity() const
{
    return blockSize_ * blockCount_;
}
