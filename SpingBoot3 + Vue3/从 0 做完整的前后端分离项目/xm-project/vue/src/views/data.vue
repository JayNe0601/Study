<template>
    <div>
        <div style="margin-bottom: 10px">
            <el-card> <!-- 卡片 -->
                <el-input
                    v-model="data.name"
                    style="width: 240px; margin-right: 10px"
                    placeholder="请输入名称查询"
                    :prefix-icon="Search"
                />
                <el-button type="primary">
                    查 询
                </el-button>
                <el-button type="primary">
                    重 置
                </el-button>
            </el-card>
        </div>
        <div style="margin-bottom: 10px">
            <el-card>
                <el-button type="primary">
                    新增
                </el-button>
                <el-button type="primary">
                    批量删除
                </el-button>
            </el-card>
        </div>
        <div>
            <el-card>
                <el-table :data="data.tableData" stripe>
                    <el-table-column prop="date" label="日期" />
                    <el-table-column prop="name" label="名称" />
                    <el-table-column prop="address" label="地址" />
                </el-table>
                <div style="margin-top: 10px">
                    <el-pagination
                        v-model:current-page="data.pageNum"
                        v-model:page-size="data.pageSize"
                        :page-Size="[5, 10, 15, 20]"
                        background
                        layout="total, sizes, prev, pager, next, jumper"
                        :total="data.total"
                    />
                </div>
            </el-card>
        </div>
    </div>
</template>

<script setup>

import {reactive} from "vue";
import { Search } from '@element-plus/icons-vue'
const data = reactive({
    name: '',
    tableData: [
        { id: 1, date: '2024-10-11', name: '张三', address: '安徽合肥' },
        { id: 2, date: '2025-10-11', name: '李四', address: '上海浦东' },
        { id: 3, date: '2024-7-15', name: '王五', address: '四川成都' },
    ],
    pageNum: 1,
    pageSize: 10,
    total: 100
})

</script>