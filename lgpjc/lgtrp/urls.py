from django.conf.urls import url

from . import views

app_name = 'lgtrp'

urlpatterns = [
    url(r'^$', views.IndexView.as_view(), name='index'),
    url(r'^student/$', views.StudentView.as_view(), name='student'),
    url(r'^school/$', views.SchoolView.as_view(), name='school'),
    url(r'^student/(?P<pk>[0-9]+)/$', views.StudentInfoView.as_view(), name='student_info'),
    url(r'^school/(?P<pk>[0-9]+)/$', views.SchoolInfoView.as_view(), name='school_info'),
]
