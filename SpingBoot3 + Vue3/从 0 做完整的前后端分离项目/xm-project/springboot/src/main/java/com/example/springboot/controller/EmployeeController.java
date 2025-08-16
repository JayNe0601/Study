package com.example.springboot.controller;

import com.example.springboot.common.Result;
import com.example.springboot.entity.Employee;
import com.example.springboot.service.EmployeeService;
import com.github.pagehelper.PageInfo;
import jakarta.annotation.Resource;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/employee")
public class EmployeeController {

    @Resource
    private EmployeeService employeeService;

    @PostMapping("/add")
    public Result add(@RequestBody Employee employee) {
        employeeService.add(employee);
        return Result.success();
    }

    @PutMapping("/update")
    public Result update(@RequestBody Employee employee) {
        employeeService.update(employee);
        return Result.success();
    }

    @DeleteMapping("/deleteById/{id}")
    public Result deleteById(@PathVariable int id) {
        employeeService.deleteById(id);
        return Result.success();
    }

    @DeleteMapping("/deleteBatch")
    public Result deleteBatch(@RequestBody List<Integer> id) {
        employeeService.deleteBatch(id);
        return Result.success();
    }


    @GetMapping("/selectAll")
    public Result selectAll(Employee employee) {
        List<Employee> list = employeeService.selectAll(employee);
        return Result.success(list);
    }

//    @GetMapping("/selectById/{id}")
//    public Result selectById(@PathVariable int id) {
//        Employee employee = employeeService.selectById(id);
//        return Result.success(employee);
//    }
    // < == 等价 == >
    @GetMapping("/selectById")
    public Result selectById(@RequestParam int id) {
        Employee employee = employeeService.selectById(id);
        return Result.success(employee);
    }

    @GetMapping("/selectByIdandNo")
    public Result selectByIdandNo(@RequestParam int id,
                                  @RequestParam String no) {
        Employee employee = employeeService.selectIdandNo(id, no);
        return Result.success(employee);
    }

    /**
     * 分页查询数据
     * pageNum  当前页码
     * pageSize 页大小
     * return
     */
    @GetMapping("/selectPage")
    public Result selectPage(
            Employee employee,
            @RequestParam(defaultValue = "1") int pageNum,
            @RequestParam(defaultValue = "10") int pageSize) {
        PageInfo<Employee> pageInfo = employeeService.selectPage(employee, pageNum, pageSize);
        return Result.success(pageInfo);
    }
}
