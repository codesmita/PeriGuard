#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dibyasmita Acharya");
MODULE_DESCRIPTION("PeriGuard Linux Character Device Driver");

#define DEVICE_NAME "periguard"

static dev_t periguard_dev;
static struct cdev periguard_cdev;
static struct class *periguard_class;
static struct device *periguard_device;

static int device_in_use = 0;

static int device_state = 0;

static char periguard_buffer[128];

static int periguard_open(struct inode *inode, struct file *file)
{
	pr_info("PeriGuard: device opened\n");
	return 0;
}
static int periguard_release(struct inode *inode, struct file *file)
{
	pr_info("PeriGuard: device released\n");
	return 0;
}
static ssize_t periguard_write(struct file *file, const char __user *buffer, size_t count, loff_t *offset)
{
	size_t bytes_to_copy;

	bytes_to_copy = count;

	if (bytes_to_copy >= sizeof(periguard_buffer))
		bytes_to_copy = sizeof(periguard_buffer) - 1;

	if (copy_from_user(periguard_buffer, buffer, bytes_to_copy))
		return -EFAULT;

	periguard_buffer[bytes_to_copy] = '\0';

	pr_info("PeriGuard: received command: %s\n", periguard_buffer);

	if (strcmp(periguard_buffer, "STATUS") == 0)
	{
		if (device_in_use ==  0)
		{
			strcpy(periguard_buffer, "AVAILABLE\n");
		}
		else
		{
			strcpy(periguard_buffer, "IN_USE\n");
		}
		pr_info("PeriGuard: STATUS command received\n");
	}
	if (strcmp(periguard_buffer, "ACCESS") == 0)
	{
		if (device_in_use == 0)
		{
			device_in_use = 1;
			strcpy(periguard_buffer, "IN_USE\n");

			pr_info("PeriGuard: access granted, device is now IN_USE\n");
		}
		else
		{
			strcpy(periguard_buffer, "DENIED\n");

			pr_info("PeriGuard: access denied, device already IN_USE\n");
		}
	}

	if (strcmp(periguard_buffer, "RELEASE") == 0)
	{
		device_in_use = 0;
		strcpy(periguard_buffer, "AVAILABLE\n");

		pr_info("PeriGuard: device released, state is now AVAILABLE\n");
	}

	if (strcmp(periguard_buffer, "FAULT") == 0)
	{
		device_state = 2;
		device_in_use = 0;

		strcpy(periguard_buffer, "FAULT\n");

		pr_info("PeriGuard: simulated fault detected\n");
	}

	if (strcmp(periguard_buffer, "RECOVERY") == 0)
	{
		device_state = 3;

		strcpy(periguard_buffer, "RECOVERY\n");

		pr_info("PeriGuard: recovery started\n");

		device_state = 0;
		device_in_use = 0;

		strcpy(periguard_buffer, "AVAILABLE\n");

		pr_info("PeriGuard: recovery successful, device is AVAILABLE\n");
	}

	*offset = 0;

	return bytes_to_copy;
}
static ssize_t periguard_read(struct file *file, char __user *buffer, size_t count, loff_t *offset)
{
	size_t data_length;

	data_length = strlen(periguard_buffer);

	if (*offset >= data_length)
		return 0;

	if (count > data_length - *offset)
		count = data_length - *offset;

	if (copy_to_user(buffer, periguard_buffer + *offset, count))
		return -EFAULT;

	*offset += count;

	return count;
}
static const struct file_operations periguard_fops =
{
	.owner = THIS_MODULE,
	.open = periguard_open,
	.release = periguard_release,
	.write = periguard_write,
	.read = periguard_read,
};
static int __init periguard_init(void)
{
	int result;

	result = alloc_chrdev_region(&periguard_dev, 0, 1, DEVICE_NAME);

	if (result < 0)
	{
		pr_err("PeriGuard: failed to allocate device number\n");
		return result;
	}

	cdev_init(&periguard_cdev, &periguard_fops);
	periguard_cdev.owner = THIS_MODULE;

	result = cdev_add(&periguard_cdev, periguard_dev, 1);

	if (result < 0)
	{
		unregister_chrdev_region(periguard_dev, 1);
		pr_err("PeriGuard: failed to add character device\n");
		return result;
	}

	periguard_class = class_create(DEVICE_NAME);

	if (IS_ERR(periguard_class))
	{
		cdev_del(&periguard_cdev);
		unregister_chrdev_region(periguard_dev, 1);
		pr_err("PeriGuard: failedto create device class\n");
		return PTR_ERR(periguard_class);
	}

	periguard_device = device_create(periguard_class, NULL, periguard_dev, NULL, DEVICE_NAME);

	if (IS_ERR(periguard_device))
	{
		class_destroy(periguard_class);
		cdev_del(&periguard_cdev);
		unregister_chrdev_region(periguard_dev, 1);
		pr_err("PeriGuard: failed to create device\n");
		return PTR_ERR(periguard_device);
	}
	pr_info("PeriGuard: device number registered\n");

	return 0;
}

static void __exit periguard_exit(void)
{
	device_destroy(periguard_class, periguard_dev);
	class_destroy(periguard_class);
	cdev_del(&periguard_cdev);
	unregister_chrdev_region(periguard_dev, 1);

	pr_info("PeriGuard: device number unregistered\n");
}

module_init(periguard_init);
module_exit(periguard_exit);

