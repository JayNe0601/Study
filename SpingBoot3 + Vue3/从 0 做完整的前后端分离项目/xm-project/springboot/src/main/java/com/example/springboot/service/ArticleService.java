package com.example.springboot.service;

import com.example.springboot.entity.Article;
import com.example.springboot.mapper.ArticleMapper;
import jakarta.annotation.Resource;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ArticleService {

    @Resource
    private ArticleMapper articleMapping;

    public List<Article> selectAll() {
        return articleMapping.selectAll();
    }

    public void update(Article article) {
        articleMapping.updateById(article);
    }
}
