package com.example.springboot.controller;

import com.example.springboot.common.Result;
import com.example.springboot.entity.Employee;
import com.example.springboot.service.EmployeeService;
import jakarta.annotation.Resource;
import org.springframework.web.bind.annotation.*;


@RestController
public class WebController {

    @Resource
    private EmployeeService employeeService;

    @GetMapping("/hello")
    public Result hello() {
        return Result.success("Hello");
    }


    @PostMapping("/login")
    public Result login(@RequestBody Employee employee) {
        Employee DbEmployee = employeeService.login(employee);
        return Result.success(DbEmployee);
    }

    @PostMapping("/register")
    public Result register(@RequestBody Employee employee) {
        employeeService.register(employee);
        return Result.success();
    }

    @PutMapping("/updatePassword")
    public Result updatePassword(@RequestBody Employee employee) {
        employeeService.updatePassword(employee);
        return Result.success();
    }
}
