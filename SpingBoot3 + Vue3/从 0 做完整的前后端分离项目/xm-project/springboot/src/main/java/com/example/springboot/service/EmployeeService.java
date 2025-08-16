package com.example.springboot.service;

import com.example.springboot.entity.Employee;
import com.example.springboot.exception.CustomException;
import com.example.springboot.mapper.EmployeeMapper;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import jakarta.annotation.Resource;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class EmployeeService {

    @Resource
    private EmployeeMapper employeeMapper;

    public List<Employee> selectAll(Employee employee) {
        return employeeMapper.selectAll(employee);
    }

    public Employee selectById(int id) {
        return employeeMapper.selectById(id);
    }

    public Employee selectIdandNo(int id, String no) {
        return employeeMapper.selectByIdandNo(id, no);
    }

    public PageInfo<Employee> selectPage(Employee employee, int pageNum, int pageSize) {
        PageHelper.startPage(pageNum, pageSize);
        List<Employee> list = employeeMapper.selectAll(employee);
        return PageInfo.of(list);
    }

    public void add(Employee employee) {employeeMapper.insert(employee);}

    public void update(Employee employee) {
        employeeMapper.updateById(employee); // 数据库里通过 id 去更新
    }

    public void deleteById(int id) {
        employeeMapper.deleteById(id);
    }

    public void deleteBatch(List<Integer> id) {
        for (Integer i : id) {
            employeeMapper.deleteById((int)i);
        }
    }

    public Employee login(Employee employee) {
        String username = employee.getUsername();
        // 查询账号是否存在
        Employee dbEmployee = employeeMapper.selectByUsername(username);
        if (dbEmployee == null) { // 没有查到这个信息，说明有这个账号
            throw new CustomException("500", "账号不存在");
        }
        // 数据库存在这个账号
        String password = employee.getPassword();
        if(!dbEmployee.getPassword().equals(password)) { // 用户输入的密码跟数据库账号的密码不匹配
            throw new CustomException("500", "账号或密码错误");
        }
        return dbEmployee;
    }

    public void register(Employee employee) {
        String username = employee.getUsername();
        Employee dbEmployee = employeeMapper.selectByUsername(username);
        // 表示注册账号已存在，不能创建
        if(dbEmployee != null) {
            throw new CustomException("500", "无法注册，账号已存在");
        }
        this.add(employee); // 新增
    }

    public void updatePassword(Employee employee) {
        Integer id = employee.getId();
        Employee dbEmployee = employeeMapper.selectById(id);
        // 页面传来的原密码与数据库密码对比不匹配
        if (!dbEmployee.getPassword().equals(employee.getPassword())) {
            throw new CustomException("500", "原密码错误");
        }
        dbEmployee.setPassword(employee.getNewPassword()); // 设置新密码
        employeeMapper.updateById(dbEmployee);
    }
}
