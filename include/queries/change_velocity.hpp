/*
    Copyright (C) 2020  University of Extremadura, University of Málaga, Blue Ocean Robotics.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Author: Renan Freitas, renan028@gmail.com
    Maintainer: Renan Freitas, renan028@gmail.com
*/

#pragma once

#include "json.hpp"
#include "change_parameter.hpp"
#include "../model/SmartsoftInf.h"
#include "../model/SmartsoftInf.cc"

namespace zmqserver
{

struct Parameter
{
  std::unordered_map<std::string, double> values;

  Parameter(double vmin, double vmax) {
    values.insert(std::make_pair("1", vmin));
    values.insert(std::make_pair("2", vmax));
  }
  Parameter() {
    values.insert(std::make_pair("1", 0.0));
    values.insert(std::make_pair("2", 0.0));
  }
};

class ChangeP: public ChangeParameter<Parameter>
{
public:
  ChangeP(int id, SmartsoftInf smartsoftInfo, Parameter values) : ChangeParameter<Parameter>(id, values)
  {
    _query["ParameterSetRepository"] = smartsoftInfo.getParameterSetRepository();
    _query["ParameterSet"] = smartsoftInfo.getParameterSet();
    _query["Component"] = smartsoftInfo.getComponent();
    _query["Parameter"] = smartsoftInfo.getParameter();
  }
  ~ChangeP(){};

  std::string dump() override
  {
    nlohmann::json values;

    values["1"] = _values.values["1"];
    values["2"] = _values.values["2"];
    _query["values"] = values;
    return Query::dump();
  }
};

} // namespace zmqserver
