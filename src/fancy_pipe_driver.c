#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>

#include "fancy_pipe.h"

static int fancy_pipe_probe(struct device *dev)
{
    printk(KERN_DEBUG "%s: probed for pipe %u\n", __FILE__, dev->id);

    return 0;
}

static int fancy_pipe_remove(struct device *dev)
{
    printk(KERN_DEBUG "%s: removed pipe %u\n", __FILE__, dev->id);

    return 0;
}

struct device_driver fancy_pipe_driver = {
    .name = "fancy_pipe",
    .bus = &fancy_pipe_bus,
    .owner = THIS_MODULE,
    .probe = fancy_pipe_probe,
    .remove = fancy_pipe_remove,
};

int fancy_pipe_driver_init(void)
{
    int ret;

    ret = driver_register(&fancy_pipe_driver);
    if (ret)
        return ret;

    return 0;
}

void fancy_pipe_driver_exit(void)
{
}
