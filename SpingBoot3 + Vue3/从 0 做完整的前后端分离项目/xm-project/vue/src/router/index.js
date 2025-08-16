import {createRouter, createWebHistory} from 'vue-router'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      redirect: '/Login',
    },
    {
      path: '/manager',
      name: 'manager',
      meta: {title: 'manager'},
      component: () => import('../views/Manager.vue'),
      children: [
          {
            path: 'home',
            name: 'home',
            meta: {title : 'home'},
            component: () => import('../views/Home.vue'),
          },
          {
            path: 'test',
            name: 'test',
            meta: {title: 'test'},
            component: () => import('../views/test.vue'),
          },
          {
            path: 'data',
            name: 'data',
            meta: {title: 'data'},
            component: () => import('../views/data.vue'),
          },
          {
            path: 'employee',
            name: 'employee',
            meta: {title: 'employee'},
            component: () => import('../views/Employee.vue'),
          },
          {
            path: 'person',
            name: 'person',
            meta: {title: 'person'},
            component: () => import('../views/Person.vue'),
          },
          {
            path: 'password',
            name: 'password',
            meta: {title : 'password'},
            component: () => import('../views/Password.vue'),
          },
      ],
    },
    {
      path: '/404',
      name: '404',
      meta: {title : '404'},
      component: () => import('../views/404.vue'),
    },
    {
      path: '/:pathMatch(.*)',
      redirect: '/404',
    },
    {
      path: '/Login',
      name: 'Login',
      meta: {title : 'Login'},
      component: () => import('../views/Login.vue'),
    },
    {
      path: '/register',
      name: 'register',
      meta: {title : 'register'},
      component: () => import('../views/Register.vue'),
    },
  ],
})

// to（跳转后的 router 对象；
// next()（调用该方法后才能进入下一个钩子））
// mate（补充路由参数的对象）
// beforeEach：跳转前的操作
router.beforeEach((to, from, next) => {
  document.title = to.meta.title;
  next()// 必须调用
})

export default router
