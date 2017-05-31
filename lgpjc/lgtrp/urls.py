from django.conf.urls import url

from . import views

app_name = 'lgtrp'

urlpatterns = [
    url(r'^$', views.IndexView.as_view(), name='index'),
    url(r'^student/$', views.StudentView.as_view(), name='student'),
    url(r'^school/$', views.SchoolView.as_view(), name='school'),
    url(r'^student/new$', views.StudentCreateView.as_view(), name='student_new'),
    url(r'^school/new$', views.SchoolCreateView.as_view(), name='school_new'),
    url(r'^student/edit/(?P<pk>[0-9]+)/$', views.StudentUpdateView.as_view(), name='student_update'),
    url(r'^school/edit/(?P<pk>[0-9]+)/$', views.SchoolUpdateView.as_view(), name='school_update'),
]
