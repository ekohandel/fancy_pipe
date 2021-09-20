#ifndef _FANCY_PIPE_H_
#define _FANCY_PIPE_H_

extern struct bus_type fancy_pipe_bus;
extern struct device_driver fancy_pipe_driver;

extern int fancy_pipe_bus_init(void);
void fancy_pipe_bus_exit(void);

int fancy_pipe_driver_init(void);
void fancy_pipe_driver_exit(void);

int fancy_pipe_device_add(long id);
int fancy_pipe_device_remove(struct device *dev, void *data);

#endif /* _FANCY_PIPE_H_ */
