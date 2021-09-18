#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>

#include "fancy_pipe.h"

int fancy_pipe_init(void)
{
    int ret;

    printk(KERN_DEBUG "%s: initializating!\n", __FILE__);

    ret = fancy_pipe_bus_init();
    if (ret)
        return ret;

    ret = fancy_pipe_driver_init();
    if (ret)
        goto driver_init_fail;

    return 0;

driver_init_fail:
    fancy_pipe_bus_exit();

    return ret;
}

void fancy_pipe_exit(void)
{
    printk(KERN_DEBUG "%s: exiting, all pipes will be removed.\n", __FILE__);

    fancy_pipe_bus_exit();
    fancy_pipe_driver_exit();
}

module_init(fancy_pipe_init);
module_exit(fancy_pipe_exit);

MODULE_LICENSE("GPL");
