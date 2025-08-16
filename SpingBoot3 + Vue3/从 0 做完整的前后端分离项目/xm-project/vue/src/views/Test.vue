<template>
    <div>
        <div style="margin-bottom: 10px">
            欢迎进入
        </div>

        <div>
            <el-icon size="50px"><View /></el-icon> 100
            <el-button type="danger" :icon="Delete" circle />
        </div>

        <div>
            路由参数 id 为 {{data.id}}
            <br>
            name 为 {{data.name}}
        </div>
    </div>
</template>

<script setup>

import {Delete} from "@element-plus/icons-vue";
import {reactive} from "vue";
import router from "@/router/index.js";

const data = reactive({
    id: router.currentRoute.value.query.id,
    name: router.currentRoute.value.query.name,
})

</script>