#include <linux/module.h>
#include <linux/device/bus.h>
#include <linux/device.h>
#include <linux/slab.h>

#include "fancy_pipe.h"

static long dev_count = 0;
struct bus_type fancy_pipe_bus = {
    .name = "fancy_pipe",
    .dev_name = "pipe",
};

static ssize_t spawn_store(struct bus_type *bus, const char *buf, size_t count)
{
    long i;
    long n;
    int ret;

    ret = kstrtol(buf, 0, &n);
    if (ret)
        return ret;

    if (n <= 0) {
        printk(KERN_ERR "%s: invalid spawn count %ld\n", __FILE__, n);
        return -EINVAL;
    }

    printk(KERN_DEBUG "%s: spawning %ld new pipes\n", __FILE__, n);
    for (i = 0; i < n; i++) {
        ret = fancy_pipe_device_spawn(dev_count++);
        if (ret)
            return ret;
    }

    return count;
}
BUS_ATTR_WO(spawn);

int fancy_pipe_bus_init(void)
{
    int ret;

    ret = bus_register(&fancy_pipe_bus);
    if (ret)
        return ret;

    ret = bus_create_file(&fancy_pipe_bus, &bus_attr_spawn);
    if (ret)
        goto spawn_attr_fail;

    return 0;

spawn_attr_fail:
    bus_unregister(&fancy_pipe_bus);

    return ret;
}

void fancy_pipe_bus_exit(void)
{
    bus_for_each_dev(&fancy_pipe_bus, NULL, NULL, fancy_pipe_device_unspawn);

    bus_remove_file(&fancy_pipe_bus, &bus_attr_spawn);
    bus_unregister(&fancy_pipe_bus);
}
