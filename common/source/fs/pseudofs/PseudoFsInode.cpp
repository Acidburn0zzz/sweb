
//
// CVS Log Info for $RCSfile: PseudoFsInode.cpp,v $
//
// $Id: PseudoFsInode.cpp,v 1.1 2005/09/17 09:33:55 davrieb Exp $
// $Log$
//
//

#include "fs/pseudofs/PseudoFsInode.h"

#include "fs/PseudoFS.h"
#include "fs/Dentry.h"

#include "util/string.h"


//----------------------------------------------------------------------
PseudoFsInode::PseudoFsInode(Superblock *super_block, uint32 inode_mode)
  : RamFsInode(super_block, inode_mode)
{
}

//----------------------------------------------------------------------
PseudoFsInode::~PseudoFsInode()
{
}

//----------------------------------------------------------------------
int32 PseudoFsInode::readData(int32 offset, int32 size, char *buffer)
{
  if (i_mode_ == I_FILE)
  {
    char* my_name = i_dentry_->getName();

    PseudoFS* pfs = PseudoFS::getInstance();
    uint8* filp =  pfs->getFilePtr(my_name);
    PseudoFS::FileIndexStruct* findx = pfs->getFileIndex(my_name);

    int32 length = findx->file_length;
    if (length < (offset + size))
    {
      return -1;
    }

    filp += offset;
    memcpy(buffer, filp, size);
    return 0;
  }

  return -1;
}

//----------------------------------------------------------------------
int32 PseudoFsInode::writeData(int32 /*offset*/, int32 /*size*/, char * /*buffer*/)
{
  return -1;
}

