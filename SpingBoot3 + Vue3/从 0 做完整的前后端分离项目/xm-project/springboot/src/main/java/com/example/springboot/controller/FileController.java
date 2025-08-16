package com.example.springboot.controller;


import cn.hutool.core.io.FileUtil;
import com.example.springboot.common.Result;
import com.example.springboot.exception.CustomException;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.io.OutputStream;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/files")
public class FileController {
    // System.getProperty("user.dir") 这个是获取到当前项目的根路径
    // 即项目 springboot 的上一级 xm-project
    // 文件上传得到目录路径
    private static final String filePath = System.getProperty("user.dir") +
            "/files/";

    @PostMapping("/upload")
    public Result upload(MultipartFile file) {
        // 通过文件流的形式接收前端发送过来的文件
        // 获取文件原始名称xxx.png / xxx.jpg
        String originalFilename = file.getOriginalFilename();
        // 判断目录是否存在 注意是导入：import cn.hutool.core.io.FileUtil;
        if(!FileUtil.isDirectory(filePath)) {
            FileUtil.mkdir(filePath);
        }
        // 给文件名加一个唯一的标识
        String fileName = System.currentTimeMillis() + "_" + originalFilename;
        // 提供文件存储的完整路径
        String realPath = filePath + fileName;
        // 写入文件
        try {
            FileUtil.writeBytes(file.getBytes(), realPath);
        } catch (IOException e) {
            throw new CustomException("500", "文件上传失败");
        }
        String url = "http://localhost:9090/files/download/" + fileName;
        return Result.success(url);
    }

    @GetMapping("/download/{fileName}")
    public void download(@PathVariable String fileName,
                         HttpServletResponse response) {
        try {
            response.addHeader("Content-Disposition", "attachment;filename=" + URLEncoder.encode(fileName, "UTF-8"));
            response.setContentType("application/octet-stream");
            // 获取输出流
            OutputStream os = response.getOutputStream();
            String realPath = filePath + fileName;
            // 获取到文件的字节数组
            byte[] bytes = FileUtil.readBytes(realPath);
            // 写入客户端
            os.write(bytes);
            // 刷新
            os.flush();
        } catch (IOException e) {
            throw new CustomException("500", "文件下载失败");
        }
    }

    @PostMapping("/wang/upload")
    public Map<String, Object> wangEditorUpload(MultipartFile file) {
        // 通过文件流的形式接收前端发送过来的文件
        // 获取文件原始名称xxx.png / xxx.jpg
        String originalFilename = file.getOriginalFilename();
        // 判断目录是否存在 注意是导入：import cn.hutool.core.io.FileUtil;
        if(!FileUtil.isDirectory(filePath)) {
            FileUtil.mkdir(filePath);
        }
        // 给文件名加一个唯一的标识
        String fileName = System.currentTimeMillis()
                + "_"
                + originalFilename;
        // 提供文件存储的完整路径
        String realPath = filePath + fileName;
        // 写入文件
        try {
            FileUtil.writeBytes(file.getBytes(), realPath);
        } catch (IOException e) {
            throw new CustomException("500", "文件上传失败");
        }
        String url = "http://localhost:9090/files/download/" + fileName;
        // wangEditor 上传图片成功后，返回的参数有所不同
        Map<String, Object> resMap = new HashMap<>();
        List<Map<String, Object>> list = new ArrayList<>();
        Map<String, Object> urlmap = new HashMap<>();
        urlmap.put("url", url);
        list.add(urlmap);
        resMap.put("error", 0);
        resMap.put("data", list);
        return resMap;
    }
}
