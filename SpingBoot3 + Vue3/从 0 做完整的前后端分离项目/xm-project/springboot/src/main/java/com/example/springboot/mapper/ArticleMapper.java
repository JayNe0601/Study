package com.example.springboot.mapper;

import com.example.springboot.entity.Article;
import org.apache.ibatis.annotations.Select;

import java.util.List;

public interface ArticleMapper {

    @Select("SELECT * FROM `article`")
    List<Article> selectAll();

    void updateById(Article article);
}
