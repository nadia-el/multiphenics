// Copyright (C) 2016-2020 by the multiphenics authors
//
// This file is part of multiphenics.
//
// multiphenics is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// multiphenics is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with multiphenics. If not, see <http://www.gnu.org/licenses/>.
//

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <dolfin/pybind11/caster_petsc.h>
#include <multiphenics/function/BlockFunction.h>
#include <multiphenics/function/BlockFunctionSpace.h>

namespace py = pybind11;

namespace multiphenics_wrappers
{
  void function(py::module& m)
  {
    // multiphenics::function::BlockFunctionSpace
    py::class_<multiphenics::function::BlockFunctionSpace, std::shared_ptr<multiphenics::function::BlockFunctionSpace>>
      (m, "BlockFunctionSpace", "A finite element block function space", py::dynamic_attr())
      .def(py::init<std::vector<std::shared_ptr<const dolfin::function::FunctionSpace>>>())
      .def(py::init<std::vector<std::shared_ptr<const dolfin::function::FunctionSpace>>,
                    std::vector<std::vector<std::shared_ptr<const dolfin::mesh::MeshFunction<std::size_t>>>>>())
      .def(py::init<std::shared_ptr<const dolfin::mesh::Mesh>,
                    std::vector<std::shared_ptr<const dolfin::fem::FiniteElement>>,
                    std::vector<std::shared_ptr<const dolfin::fem::DofMap>>>())
      .def(py::init<std::shared_ptr<const dolfin::mesh::Mesh>,
                    std::vector<std::shared_ptr<const dolfin::fem::FiniteElement>>,
                    std::vector<std::shared_ptr<const dolfin::fem::DofMap>>,
                    std::vector<std::vector<std::shared_ptr<const dolfin::mesh::MeshFunction<std::size_t>>>>>())
      .def("__eq__", &multiphenics::function::BlockFunctionSpace::operator==)
      .def("dim", &multiphenics::function::BlockFunctionSpace::dim)
      .def("contains", &multiphenics::function::BlockFunctionSpace::contains)
      .def_property_readonly("elements", &multiphenics::function::BlockFunctionSpace::elements)
      .def_property_readonly("mesh", &multiphenics::function::BlockFunctionSpace::mesh)
      .def_property_readonly("dofmaps", &multiphenics::function::BlockFunctionSpace::dofmaps)
      .def_property_readonly("block_dofmap", &multiphenics::function::BlockFunctionSpace::block_dofmap)
      .def("sub", (std::shared_ptr<dolfin::function::FunctionSpace> (multiphenics::function::BlockFunctionSpace::*)(std::size_t) const)
           &multiphenics::function::BlockFunctionSpace::sub)
      .def("extract_block_sub_space", &multiphenics::function::BlockFunctionSpace::extract_block_sub_space)
      .def("tabulate_dof_coordinates", &multiphenics::function::BlockFunctionSpace::tabulate_dof_coordinates);
      
    // multiphenics::function::BlockFunction
    py::class_<multiphenics::function::BlockFunction, std::shared_ptr<multiphenics::function::BlockFunction>>
      (m, "BlockFunction", "A finite element block function")
      .def(py::init<std::shared_ptr<const multiphenics::function::BlockFunctionSpace>>(), "Create a function on the given block function space")
      .def(py::init<std::shared_ptr<const multiphenics::function::BlockFunctionSpace>, std::vector<std::shared_ptr<dolfin::function::Function>>>())
      .def(py::init<std::shared_ptr<const multiphenics::function::BlockFunctionSpace>, Vec>())
      .def(py::init<std::shared_ptr<const multiphenics::function::BlockFunctionSpace>, Vec,
                    std::vector<std::shared_ptr<dolfin::function::Function>>>())
      .def("sub", &multiphenics::function::BlockFunction::operator[])
      .def_property_readonly("block_vector", &multiphenics::function::BlockFunction::block_vector, "Return the block vector associated with the finite element BlockFunction")
      .def("apply", &multiphenics::function::BlockFunction::apply);
  }
}