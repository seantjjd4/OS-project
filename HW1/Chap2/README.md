# Linux Kernel Modules
### Part I: Creating, loading, and removing kernel modules
* Proceed through the steps described above to create the kernel module and to load and unload the module. Be sure to check the counters of the kernel log buffer using dmesg to ensure you have properly followed the steps.
### Part II: Creating, traversing, and deleting kernel data structures
* In the module entry point, create a linked list containing five struct_birthday elements. Traverse the linked list and output its contents to the kernel log buffer. Invoke the dmesg command to ensure the list is properly constructed once the kernel module has been loaded.
* In the module exit point, delete the elements from the linked list and return the free memory back to the kernel. Again, invoke the dmesg command to check that the list has been removed once the kernel module has been unloaded.
