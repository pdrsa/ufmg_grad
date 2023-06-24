<template>
  <v-container>
    <v-row>
      <GroupName/>
    </v-row>
    <v-row>
      <GroupMembers/>
    </v-row>
    <v-row>
      <GroupPosts/>
    </v-row>
  </v-container>
</template>
<script>
export default {
  components:{
    GroupName: () => import('@/components/GroupNameComponent.vue'),
    GroupMembers: () => import('@/components/GroupMembersComponent.vue'),
    GroupPosts: () => import('@/components/GroupPostsComponent.vue')
  }
};
</script>
<style>
</style>
