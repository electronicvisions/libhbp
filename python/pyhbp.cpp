#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Werror"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wuseless-cast"
#pragma GCC diagnostic ignored "-Wpedantic"
#include <pybind11/pybind11.h>
#pragma GCC diagnostic pop

#include <extoll/extoll.h>
#include <extoll/register_file.h>

namespace py = pybind11;

using namespace extoll::library;


RegisterFile register_file(RMA2_Nodeid node)
{
    return Extoll::Instance().register_file(node);
}



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
PYBIND11_MODULE(pyhbp, m)
{
    m.doc() = "Extoll libhbp python bindings2";

    m.def("register_file", &register_file, py::return_value_policy::move);

    using rf_read = uint64_t (RegisterFile::*)(RMA2_NLA) const;
    using rf_write = void (RegisterFile::*)(RMA2_NLA, uint64_t);

    py::class_<RegisterFile>(m, "RegisterFile")
           .def("read", static_cast<rf_read>(&RegisterFile::read))
           .def("write", static_cast<rf_write>(&RegisterFile::write))
           ;

    auto address = py::enum_<Address>(m, "Address");
    address.value("Driver", 1);
    address.export_values();
}
#pragma GCC diagnostic pop