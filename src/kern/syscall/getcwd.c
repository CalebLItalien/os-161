#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <uio.h>
#include <proc.h>
#include <current.h>
#include <syscall.h>
#include <vnode.h>
#include <vfs.h>
#include <kern/fcntl.h>
#include <copyinout.h>
#include <file_table.h>

int
sys___getcwd(char *buf, size_t buflen){
    struct uio uio;
    struct iovec iov;
    char tmp_buf[(int) buflen];
    int result;
    char tmp;

    
    //spinlock_acquire(&curproc->p_lock);
    result = copyin((const_userptr_t) buf, &tmp, sizeof(char));
    if(result){
        return -result;
    }

    if(buf == NULL){
        //spinlock_release(&curproc->p_lock);
        return -EFAULT;
    }

    if(buflen < 1){
        //spinlock_release(&curproc->p_lock);
        return -EFAULT;
    }
    
    if(curproc -> p_cwd == NULL){
        //spinlock_release(&curproc->p_lock);
        return -ENOENT;
    }

    uio_kinit(&iov, &uio, tmp_buf, buflen, 0, UIO_READ);

    result = vfs_getcwd(&uio);
    if(result){
        //spinlock_release(&curproc->p_lock);
        return -result;
    }

    size_t *got = NULL;
    result = copyoutstr((const void *) tmp_buf, (userptr_t) buf, buflen, got);
    if(result){
        //spinlock_release(&curproc->p_lock);
        return -EFAULT;
    }

    int ret = (int) &got;
    //spinlock_release(&curproc->p_lock);
    return ret;
}