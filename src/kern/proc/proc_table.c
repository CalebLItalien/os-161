#include <proc_table.h>
#include <types.h>
#include <lib.h>
#include <synch.h>
#include <proc.h>

#define MAX_ACTIVE_PROCS 100

void proc_table_create(struct proc_table ** pt){
    /*
    Creates a process table.
    */
    *pt = kmalloc(sizeof(struct proc_table));
    if (*pt == NULL) { kprintf("Hey! Where's my process table?")};

    spinlock_init(&((*pt) -> pt_lock));
    *pt -> active_procs = 0;
}

void proc_table_destroy(struct proc_table * pt){
    /*
    Deallocates space for a process table
    */
    KASSERT(pt != NULL);

    if (pt -> active_procs != 0){
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < MAX_ACTIVE_PROCS; j++){
                if (pt -> proc_table_map[i][j].procPtr != NULL){ proc_destroy(pt -> proc_table_map[i][j].procPtr);}
            }
        }
        kfree(pt -> proc_table_map[i]);
    }
    spinlock_cleanup(&pt->pt_lock);
    kfree(pt);
}

int add_proc(int pid, struct proc_table *pt, struct proc * p){
    /*
    Adds a process to the process table, if not full. Returns 0 upon success, else an error. 
    */
    KASSERT(pt != NULL);

    if (proc_table_full(pt)) { return -1; }

    int available_pid = get_available_pid(pt);

    pt -> proc_table_map

}

int get_proc(int pid, struct proc_table *pt, struct proc **p){
    /*
    Returns a process from the process table, given a pid. Returns 0 upon success, else an error. */
}

int get_available_pid(struct proc_table *pt){
    /*
    Gets the next available pid
    */
}

bool proc_table_full(struct proc_table *pt){
    /*
    Returns whether or not the process table is funn
    */
}

struct proc * remove_process(struct proc_table *pt, int pid){
    /*
    Removes a process from the process table
    */
}
