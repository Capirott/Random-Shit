from django.conf.urls import url

from . import views

app_name = 'lgtrp'

urlpatterns = [
    url(r'^$', views.IndexView.as_view(), name='index'),
    url(r'^student/(?P<pk>[0-9]+)/$', views.StudentView.as_view(), name='student'),
    url(r'^school/(?P<pk>[0-9]+)/$', views.SchoolView.as_view(), name='school'),
]
