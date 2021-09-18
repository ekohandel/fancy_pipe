
#include <linux/module.h>
#include <linux/device/bus.h>
#include <linux/device.h>
#include <linux/slab.h>

#include "fancy_pipe.h"

static void fancy_pipe_device_release(struct device *dev)
{
}

int fancy_pipe_device_spawn(long id)
{
    int ret;
    struct device *dev;

    dev = kzalloc(sizeof(struct device), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;

    dev->id = id;
    dev->bus = &fancy_pipe_bus;
    dev->release = fancy_pipe_device_release;

    printk(KERN_DEBUG "%s: spawning pipe %lu\n", __FILE__, id);

    ret = device_register(dev);
    if (ret)
        goto dev_reg_fail;

    return 0;

dev_reg_fail:
    kfree(dev);

    return ret;
}

int fancy_pipe_device_unspawn(struct device *dev, void *data)
{
    printk(KERN_DEBUG "%s: unspawning pipe %u\n", __FILE__, dev->id);

    device_unregister(dev);

    kfree(dev);

    return 0;
}