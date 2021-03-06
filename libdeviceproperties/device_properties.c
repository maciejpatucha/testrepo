#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <device_properties.h>

static void PrintAndroidProps(androidprops_t *props);
static void PrintiOSProps(iosprops_t *props);
static char *GetPhoneString(iosdevice_t deviceType);
static void RemoveNewLine(char *string, int stringLen);

androidprops_t *CreateAndroidProperties(char *deviceID,
                                        char *deviceManufacturer,
                                        char *deviceModel,
                                        char *androidVersion)
{
    androidprops_t *newProps = calloc(1, sizeof(androidprops_t));

    if (newProps == NULL)
    {
        printf("Failed to allocate memory for new properties\n");
        return NULL;
    }

    strncpy(newProps->deviceID, deviceID, sizeof(newProps->deviceID));
    strncpy(newProps->deviceManufacturer, deviceManufacturer, sizeof(newProps->deviceManufacturer));
    strncpy(newProps->deviceModel, deviceModel, sizeof(newProps->deviceModel));
    strncpy(newProps->androidVersion, androidVersion, sizeof(newProps->androidVersion));

    RemoveNewLine(newProps->deviceID, strlen(newProps->deviceID));
    RemoveNewLine(newProps->deviceManufacturer, strlen(newProps->deviceManufacturer));
    RemoveNewLine(newProps->deviceModel, strlen(newProps->deviceModel));
    RemoveNewLine(newProps->androidVersion, strlen(newProps->androidVersion));

    return newProps;
}

iosprops_t *CreateiOSProperties(char *udid,
                                char *deviceName,
                                iosdevice_t deviceType,
                                char *osVersion)
{
    iosprops_t *newProps = calloc(1, sizeof(iosprops_t));

    if (newProps == NULL)
    {
        printf("Failed to allocate memory for new properties\n");
        return NULL;
    }

    strncpy(newProps->udid, udid, sizeof(newProps->udid));
    strncpy(newProps->deviceName, deviceName, sizeof(newProps->deviceName));
    newProps->deviceType = deviceType;
    strncpy(newProps->osVersion, osVersion, sizeof(newProps->osVersion));

    RemoveNewLine(newProps->udid, strlen(newProps->udid));
    RemoveNewLine(newProps->deviceName, strlen(newProps->deviceName));
    RemoveNewLine(newProps->osVersion, strlen(newProps->osVersion));

    return newProps;
}

void PrintProperties(proptype_t propType, void *props)
{
    androidprops_t *androidProps = NULL;
    iosprops_t *iosProps = NULL;

    switch(propType)
    {
    case ANDROID:
        androidProps = (androidprops_t *)props;
        PrintAndroidProps(androidProps);
        break;
    case IOS:
        iosProps = (iosprops_t *)props;
        PrintiOSProps(iosProps);
        break;
    }
}

void CleanupProperties(proptype_t propType, void *props)
{
    androidprops_t *androidProps = NULL;
    iosprops_t *iosProps = NULL;

    switch(propType)
    {
    case ANDROID:
        androidProps = (androidprops_t *)props;
        free(androidProps);
        break;
    case IOS:
        iosProps = (iosprops_t *)props;
        free(iosProps);
        break;
    }
}

static void PrintAndroidProps(androidprops_t *props)
{
    printf("Android Device properties:\n"
           "----------------------------------------------------\n"
           "Device ID:\t\t\t%s\n"
           "Device Manufacturer:\t\t%s\n"
           "Device Model:\t\t\t%s\n"
           "Android Vesion:\t\t\t%s\n"
           "----------------------------------------------------\n",
           props->deviceID,
           props->deviceManufacturer,
           props->deviceModel,
           props->androidVersion);

}

static void PrintiOSProps(iosprops_t *props)
{
    printf("iOS Device properties:\n"
           "----------------------------------------------------\n"
           "UDID:\t\t\t\t%s\n"
           "Device Name:\t\t\t%s\n"
           "Device Type:\t\t\t%s\n"
           "iOS Vesion:\t\t\t%s\n"
           "----------------------------------------------------\n",
           props->udid,
           props->deviceName,
           GetPhoneString(props->deviceType),
           props->osVersion);
}

static char *GetPhoneString(iosdevice_t deviceType)
{
    char *deviceString[17] = {
        "iPhone4",
        "iPhone4s",
        "iPhone5",
        "iPhone5c",
        "iPhone5s",
        "iPhone6",
        "iPhone6Plus",
        "iPad",
        "iPad2",
        "iPad3",
        "iPad4",
        "iPadAir",
        "iPadAir2",
        "iPadMini",
        "iPadMini2",
        "iPadMini3",
        "Unknown device"
    };

    return deviceString[deviceType];
}

static void RemoveNewLine(char *string, int stringLen)
{
    char *tmp = strchr(string, '\n');

    if (tmp != NULL)
    {
        *tmp = 0;
    }
}
