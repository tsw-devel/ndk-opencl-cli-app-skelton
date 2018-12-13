/**
 * Android-NDK OpenCL CLI App skelton on Smartphone with Snapdragon.
 * Sample : OpenCL device summary program
 */
#include <iostream>
#include <vector>

#define CL_TARGET_OPENCL_VERSION 200
#include <CL/cl.h>

namespace {

template <typename T>
struct cl_query_info {
  const char *name;
  const T val;
};

#define query_data(name)  { #name, name }
constexpr cl_query_info<cl_platform_info> kPlatformInfoQueryTable[] = {
    query_data(CL_PLATFORM_VENDOR), query_data(CL_PLATFORM_NAME),
    // query_data(CL_PLATFORM_VERSION),
    // query_data(CL_PLATFORM_PROFILE),
    // query_data(CL_PLATFORM_EXTENSIONS)
};
constexpr cl_query_info<cl_device_info> kDeviceInfoQueryTable[] = {
    query_data(CL_DEVICE_NAME),    query_data(CL_DRIVER_VERSION),
    query_data(CL_DEVICE_PROFILE), query_data(CL_DEVICE_VERSION),
    // query_data(CL_DEVICE_OPENCL_C_VERSION),
    // query_data(CL_DEVICE_EXTENSIONS)
};

int query_cl_device_sumary(cl_device_type device_type) {
  char query_buf[1024] = {0};
  constexpr std::ostream &kMsgOut = std::cout;
  constexpr std::ostream &kErrOut = std::cerr;
  constexpr int kQueryError = -1;
  
  // Query platform num
  cl_uint platform_num;
  cl_int status = clGetPlatformIDs(0, NULL, &platform_num);
  if (status != CL_SUCCESS) {
    kErrOut << "clGetPlatformIDs() : error" << std::endl;
    return kQueryError;
  } else if (platform_num < 1) {
    kErrOut << "clGetPlatformIDs() : Platform not found." << std::endl;
    return kQueryError;
  }

  std::vector<cl_platform_id> platform_ids(platform_num);
  status = clGetPlatformIDs(platform_num, &platform_ids.front(), &platform_num);
  if (status != CL_SUCCESS) {
    kErrOut << "clGetPlatformIDs() : error" << std::endl;
    return kQueryError;
  }

  // Enumerate platforms
  for (const auto &pfid : platform_ids) {
    // Query platform char[] info
    for (const auto &query : kPlatformInfoQueryTable) {
      status = clGetPlatformInfo(pfid, query.val, sizeof(query_buf), query_buf, NULL);
      if (status != CL_SUCCESS) {
        kErrOut << "clGetPlatformInfo(" << query.name << ") : error" << std::endl;
        return kQueryError;
      }
      kMsgOut << query.name << "\t" << query_buf << std::endl;
    }

    // Query device num
    cl_uint device_num;
    status = clGetDeviceIDs(pfid, device_type, 0, NULL, &device_num);
    if (status != CL_SUCCESS) {
      kErrOut << "clGetDeviceIDs() : error" << std::endl;
      return kQueryError;
    }
    std::vector<cl_device_id> device_ids(device_num);
    kMsgOut << "CL DEVICE NUM \t\t" << device_num << std::endl;
    status = clGetDeviceIDs(pfid, CL_DEVICE_TYPE_ALL, device_num,
                            &device_ids.front(), &device_num);
    // Enumerate devices
    for (const auto &devid : device_ids) {
      // Query device char[] info
      for (const auto &query : kDeviceInfoQueryTable) {
        status = clGetDeviceInfo(devid, query.val, sizeof(query_buf), query_buf, NULL);
        if (status != CL_SUCCESS) {
          kErrOut << "clGetDeviceInfo(" << query.name << ") : error" << std::endl;
          return kQueryError;
        }
        kMsgOut << query.name << "\t" << query_buf << std::endl;
      }

      // Query NDRange
      cl_uint ndrange;
      status = clGetDeviceInfo(devid, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
                               sizeof(ndrange),
                               &ndrange, NULL);
      if (status != CL_SUCCESS) {
        kErrOut << "clGetDeviceInfo(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS) : error" << std::endl;
        return kQueryError;
      }
      
      std::vector<size_t> work_item_sizes(ndrange);
      status = clGetDeviceInfo(devid, CL_DEVICE_MAX_WORK_ITEM_SIZES,
                               work_item_sizes.size() * sizeof(size_t),
                               &work_item_sizes.front(), NULL);
      if (status != CL_SUCCESS) {
        kErrOut << "clGetDeviceInfo(CL_DEVICE_MAX_WORK_ITEM_SIZES) : error" << std::endl;
        return kQueryError;
      }
      kMsgOut << "CL_DEVICE_MAX_WORK_ITEM_SIZES" << "\t\t";
      for (size_t sz : work_item_sizes) {
        kMsgOut << sz << " ";
      }
      kMsgOut << std::endl;

      // Query SVM
      cl_device_svm_capabilities svm_caps;
      status = clGetDeviceInfo(devid, CL_DEVICE_SVM_CAPABILITIES,
                               sizeof(cl_device_svm_capabilities), &svm_caps, NULL);
      kMsgOut << std::boolalpha;
      kMsgOut << "CL_DEVICE_SVM_COARSE_GRAIN_BUFFER" << "\t" << (0 != (CL_DEVICE_SVM_COARSE_GRAIN_BUFFER & svm_caps)) << std::endl;
      kMsgOut << "CL_DEVICE_SVM_FINE_GRAIN_BUFFER" << "\t\t" << (0 != (CL_DEVICE_SVM_FINE_GRAIN_BUFFER & svm_caps)) << std::endl;
      kMsgOut << "CL_DEVICE_SVM_FINE_GRAIN_SYSTEM" << "\t\t" << (0 != (CL_DEVICE_SVM_FINE_GRAIN_SYSTEM & svm_caps)) << std::endl;
      kMsgOut << "CL_DEVICE_SVM_ATOMICS" << "\t\t\t" << (0 != (CL_DEVICE_SVM_ATOMICS & svm_caps)) << std::endl;
      kMsgOut << std::noboolalpha;
    }
  }
  return 0;
}
}  // namespace

int main(int argc, const char *argv[]) {
  int ret;
  ret = query_cl_device_sumary(CL_DEVICE_TYPE_ALL);

  return ret;
}
