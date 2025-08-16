package com.example.springboot.controller;


import com.example.springboot.common.Result;
import com.example.springboot.entity.Article;
import com.example.springboot.service.ArticleService;
import jakarta.annotation.Resource;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/article")
public class ArticleController {

    @Resource
    private ArticleService articleService;


    @GetMapping("/selectAll")
    public Result selectAll() {
        List<Article> articles = articleService.selectAll();
        return Result.success(articles);
    }

    @PutMapping("update")
    public Result update(@RequestBody Article article) {
        articleService.update(article);
        return Result.success();
    }
}
