#include <utils/DPCPP.h>

#include <ATen/Config.h>
#include <ATen/Context.h>
#include <c10/util/Exception.h>

#include <core/Allocator.h>
#include <core/Convertor.h>
#include <core/Device.h>
#include <core/Generator.h>
#include <core/detail/Hooks.h>
#include <runtime/Device.h>
#include <runtime/Exception.h>

#include <cstddef>
#include <functional>
#include <memory>

namespace xpu {
namespace dpcpp {
namespace detail {

void XPUHooks::initXPU() const {
  // TODO:
}

bool XPUHooks::hasXPU() const {
  return true;
}

std::string XPUHooks::showConfig() const {
  return "XPU backend version: 1.0";
}

at::Device XPUHooks::getATenDeviceFromDLPackDevice(
    const DLDevice_& dl_device,
    void* data) const {
  return getATenDeviceFromUSM(data, dl_device.device_id);
}

DLDevice_& XPUHooks::getDLPackDeviceFromATenDevice(
    DLDevice_& dl_device,
    const at::Device& aten_device,
    void* data) const {
  TORCH_CHECK(aten_device.is_xpu(), "Only the XPU device type is expected.");
  sycl::device& xpu_device = xpu::dpcpp::dpcppGetRawDevice(aten_device.index());

  // After device hierarchy is controled by driver, all the components use the
  // same device partition mode. So we don't need to find the parent device
  // anymore and directly find position of sycl device `xpu_device` in
  // sycl::device::get_devices()
  auto device_list = sycl::device::get_devices();
  auto beg = std::begin(device_list);
  auto end = std::end(device_list);
  auto selector_fn = [xpu_device](const sycl::device& device) -> bool {
    return xpu_device == device;
  };
  auto pos = find_if(beg, end, selector_fn);

  TORCH_CHECK(pos != end, "Could not produce DLPack: failed finding device_id");
  std::ptrdiff_t dev_idx = std::distance(beg, pos);

  dl_device = {kDLOneAPI, dev_idx};

  return dl_device;
}

Generator XPUHooks::getXPUGenerator(DeviceIndex device_index) const {
  auto generator = make_generator<xpu::dpcpp::DPCPPGeneratorImpl>(device_index);
  return generator;
}

const Generator& XPUHooks::getDefaultXPUGenerator(
    DeviceIndex device_index) const {
  const auto& generator = getDefaultDPCPPGenerator(device_index);
  return generator;
}

int XPUHooks::getNumGPUs() const {
  return xpu::dpcpp::device_count();
}

REGISTER_XPU_HOOKS(XPUHooks);

} // namespace detail
} // namespace dpcpp
} // namespace xpu
